// Ref: https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/fenwicktree.rs
pub struct FenwickTree {
    n: usize,
    bit: Vec<Vec<i64>>,
    uses_raq: bool,
}
impl FenwickTree {
    pub fn new(n: usize) -> Self {
        FenwickTree {
            n,
            bit: vec![vec![0; n]; 2],
            uses_raq: false,
        }
    }
    fn accum_sub(&self, is_raq: usize, mut i: usize) -> i64 {
        let mut sum = 0;
        while i > 0 {
            sum += self.bit[is_raq][i - 1];
            i &= i - 1;
        }
        sum
    }
    fn add_sub(&mut self, is_raq: usize, mut i: usize, x: i64) {
        while i <= self.n {
            self.bit[is_raq][i - 1] += x;
            i += i & i.wrapping_neg();
        }
    }
    /// performs data[i] += val;
    pub fn add(&mut self, mut i: usize, x: i64) {
        assert!(i <= self.n);
        i += 1;
        self.add_sub(0, i, x);
    }
    /// performs data[l], ..., data[r - 1] += val;
    pub fn range_add(&mut self, mut l: usize, mut r: usize, x: i64) {
        assert!(l <= r && r <= self.n);
        l += 1;
        r += 1;
        self.uses_raq = true;
        self.add_sub(0, l, -x * (l as i64 - 1));
        self.add_sub(0, r, x * (r as i64 - 1));
        self.add_sub(1, l, x);
        self.add_sub(1, r, -x);
    }
    fn accum(&self, i: usize) -> i64 {
        if self.uses_raq {
            self.accum_sub(0, i) + self.accum_sub(1, i) * i as i64
        } else {
            self.accum_sub(0, i)
        }
    }
    /// Returns data[l] + ... + data[r - 1].
    pub fn sum(&self, l: usize, r: usize) -> i64 {
        assert!(l <= r && r <= self.n);
        self.accum(r) - self.accum(l)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn fenwick_tree_works() {
        let mut ft = FenwickTree::new(5);
        // [1, 1, 1, 1, 1]
        ft.range_add(0, 5, 1);
        for i in 0..5 {
            assert_eq!(ft.sum(i, i + 1), 1);
        }

        let mut ft = FenwickTree::new(5);
        // [1, 2, 3, 4, 5]
        for i in 0..5 {
            ft.add(i, i as i64 + 1);
        }
        assert_eq!(ft.sum(0, 4), 10);
        assert_eq!(ft.sum(0, 5), 15);
        assert_eq!(ft.sum(3, 4), 4);
        assert_eq!(ft.sum(3, 5), 9);
    }
}
