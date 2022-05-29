// Lazy Segment Tree
//
// # Refs
// - https://atcoder.jp/contests/abc032/submissions/27759184, yokofudori
struct SegmentTree<S, Op, F, Mapping, Composition> {
    n0: usize,
    n: usize,
    s: S,
    op: Op,
    f: F,
    mapping: Mapping,
    composition: Composition,
    data: Vec<S>,
    lazy: Vec<F>,
}
#[allow(dead_code)]
impl<S, Op, F, Mapping, Composition> SegmentTree<S, Op, F, Mapping, Composition>
where
    S: Copy + PartialEq + std::fmt::Debug,
    Op: Fn(S, S) -> S,
    F: Copy + PartialEq + std::fmt::Debug,
    Mapping: Fn(F, S) -> S,
    Composition: Fn(F, F) -> F,
{
    pub fn new(n0: usize, s: S, op: Op, f: F, mapping: Mapping, composition: Composition) -> Self {
        debug_assert_eq!(op(s, s), s);
        debug_assert_eq!(mapping(f, s), s);
        debug_assert_eq!(composition(f, f), f);
        let n = 1 << (31 - (2 * n0 as i32 - 1).leading_zeros() as usize);
        Self {
            n0,
            n,
            s,
            op,
            f,
            mapping,
            // composition(f1, f2) -> f2(f1(x))
            composition,
            data: vec![s; n << 1],
            lazy: vec![f; n << 1],
        }
    }
    pub fn set(&mut self, i: usize, x: S) {
        assert!(i < self.n0);
        self.prod(i, i + 1);
        let mut i = i + self.n;
        self.data[i] = x;
        while i > 1 {
            // i = (i - 1) / 2;
            i >>= 1;
            self.data[i] = (self.op)(self.data[i << 1], self.data[i << 1 | 1]);
            self.lazy[i] = self.f;
        }
    }
    #[inline]
    fn eval(&mut self, k: usize) {
        if self.lazy[k] == self.f {
            return;
        }
        if k < self.n {
            self.lazy[k << 1] = (self.composition)(self.lazy[k << 1], self.lazy[k]);
            self.lazy[k << 1 | 1] = (self.composition)(self.lazy[k << 1 | 1], self.lazy[k]);
        }
        self.data[k] = (self.mapping)(self.lazy[k], self.data[k]);
        self.lazy[k] = self.f;
    }
    fn apply_sub(&mut self, a: usize, b: usize, y: F, k: usize, l: usize, r: usize) -> S {
        self.eval(k);
        if r <= a || b <= l {
            return self.data[k];
        }
        if a <= l && r <= b {
            self.lazy[k] = (self.composition)(self.lazy[k], y);
            return (self.mapping)(self.lazy[k], self.data[k]);
        }
        let vr = self.apply_sub(a, b, y, k << 1, l, (l + r) >> 1);
        let vl = self.apply_sub(a, b, y, k << 1 | 1, (l + r) >> 1, r);
        self.data[k] = (self.op)(vr, vl);
        self.data[k]
    }
    pub fn apply(&mut self, a: usize, b: usize, x: F) {
        assert!(a <= b && b <= self.n0);
        self.apply_sub(a, b, x, 1, 0, self.n);
    }
    fn prod_sub(&mut self, a: usize, b: usize, k: usize, l: usize, r: usize) -> S {
        self.eval(k);
        if r <= a || b <= l {
            self.s
        } else if a <= l && r <= b {
            self.data[k]
        } else {
            let vl = self.prod_sub(a, b, k << 1, l, (l + r) >> 1);
            let vr = self.prod_sub(a, b, k << 1 | 1, (l + r) >> 1, r);
            (self.op)(vl, vr)
        }
    }
    pub fn prod(&mut self, a: usize, b: usize) -> S {
        assert!(a <= b && b <= self.n0);
        self.prod_sub(a, b, 1, 0, self.n)
    }
    pub fn raw(&mut self) -> Vec<S> {
        let mut res = vec![self.s; self.n0];
        for i in 0..self.n0 {
            res[i] = self.prod(i, i + 1);
        }
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn raq_rmaxq_works() {
        let n = 5;
        // RAQ
        let s = std::i32::MIN;
        let op = |s1: i32, s2: i32| s1.max(s2);
        // RMaxQ
        let f = 0;
        let mg = |f1: i32, s1: i32| f1 + s1;
        let cn = |f1: i32, f2: i32| f1 + f2;
        // RAQ, RMaxQ
        let mut st = SegmentTree::new(n, s, op, f, mg, cn);

        st.set(0, 3);
        st.set(1, 1);
        st.set(2, 4);
        st.set(3, 1);
        st.set(4, 5);
        assert_eq!(st.raw(), [3, 1, 4, 1, 5]);

        for i in 0..n {
            // [i, i)
            assert_eq!(st.prod(i, i), std::i32::MIN);
        }

        assert_eq!(st.prod(0, 1), 3);
        assert_eq!(st.prod(0, 2), 3);
        assert_eq!(st.prod(0, 3), 4);
        assert_eq!(st.prod(0, 4), 4);
        assert_eq!(st.prod(0, 5), 5);

        assert_eq!(st.prod(0, 3), 4);
        assert_eq!(st.prod(1, 3), 4);
        assert_eq!(st.prod(2, 3), 4);

        st.apply(1, 4, 100);
        assert_eq!(st.raw(), [3, 101, 104, 101, 5]);
    }
    #[test]
    fn rsq_ruq_works() {
        let n = 5;
        // RSQ
        let s = (0, 0); // (val, size)
        let op = |s1: (i64, usize), s2: (i64, usize)| (s1.0 + s2.0, s1.1 + s2.1);
        // RUQ
        let f = std::i64::MAX;
        let mg = |f1: i64, mut s1: (i64, usize)| {
            if f1 != f {
                s1.0 = f1 * s1.1 as i64;
            }
            s1
        };
        let cn = |f1: i64, f2: i64| if f1 != f { f1 } else { f2 };
        // RSQ, RUQ
        let mut st = SegmentTree::new(n, s, op, f, mg, cn);

        st.set(0, (3, 1));
        st.set(1, (1, 1));
        st.set(2, (4, 1));
        st.set(3, (1, 1));
        st.set(4, (5, 1));
        let unpack = |a: Vec<(i64, usize)>| {
            a.iter().map(|&a| a.0).collect::<Vec<i64>>()
        };
        assert_eq!(unpack(st.raw()), [3, 1, 4, 1, 5]);

        assert_eq!(st.prod(0, 1).0, 3);
        assert_eq!(st.prod(0, 2).0, 4);
        assert_eq!(st.prod(0, 3).0, 8);
        assert_eq!(st.prod(0, 4).0, 9);
        assert_eq!(st.prod(0, 5).0, 14);

        assert_eq!(st.prod(0, 3).0, 8);
        assert_eq!(st.prod(1, 3).0, 5);
        assert_eq!(st.prod(2, 3).0, 4);

        st.apply(1, 4, 283);
        assert_eq!(unpack(st.raw()), [3, 283, 283, 283, 5]);
    }
}
