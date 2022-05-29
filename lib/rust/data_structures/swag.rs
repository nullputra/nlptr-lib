/// F must give a semigroup: it is required that F satisfies associativity.
/// Commutativity and existence of the identity are not required.
/// Ref:
///   https://scrapbox.io/data-structures/Sliding_Window_Aggregation
///   https://github.com/koba-e964/sliding-window-aggregation/blob/master/src/lib.rs, kobae964
#[allow(dead_code)]
struct SWAg<T, F> {
    back: Vec<T>,
    back_agg: Vec<T>,
    front: Vec<T>,
    front_agg: Vec<T>,
    f: F,
}
#[allow(dead_code)]
impl<T: Copy + std::default::Default + std::cmp::PartialEq, F: Fn(T, T) -> T> SWAg<T, F> {
    fn new(f: F) -> Self {
        let def = Default::default();
        debug_assert!(f(def, def) == def);
        SWAg {
            back: Vec::new(),
            back_agg: Vec::new(),
            front: Vec::new(),
            front_agg: Vec::new(),
            f,
        }
    }
    fn fold(&self) -> Option<T> {
        match (self.back_agg.last(), self.front_agg.last()) {
            (None, None) => None,
            (None, x) => x.cloned(),
            (x, None) => x.cloned(),
            (Some(&x), Some(&y)) => Some((self.f)(x, y)),
        }
    }
    // push_back
    fn push(&mut self, x: T) {
        let last = self.front_agg.last().cloned();
        self.front.push(x);
        self.front_agg.push(match last {
            None => x,
            Some(y) => (self.f)(y, x),
        });
    }
    // pop_front
    fn pop(&mut self) -> Option<T> {
        if let Some(x) = self.back.pop() {
            return Some(x);
        };
        std::mem::swap(&mut self.front, &mut self.back);
        self.back.reverse();
        let res = self.back.pop();
        let len = self.back.len();
        self.back_agg = Vec::with_capacity(self.back.len());
        if len > 0 {
            self.back_agg.push(self.back[0]);
            let mut cur = self.back[0];
            for i in 1..len {
                cur = (self.f)(self.back[i], cur);
                self.back_agg.push(cur);
            }
        }
        self.front = Vec::new();
        self.front_agg = Vec::new();
        res
    }
}
use std::fmt;
impl<T: Copy + std::default::Default + std::cmp::PartialEq + fmt::Debug, F: Fn(T, T) -> T>
    fmt::Debug for SWAg<T, F>
{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut a = vec![];
        for &back in self.back.iter().rev() {
            a.push(back);
        }
        for &front in self.front.iter() {
            a.push(front);
        }
        a.fmt(f)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn fold_works() {
        let mut sw = SWAg::<i32, _>::new(|x, y| x + y);
        sw.push(3);
        sw.push(4);
        sw.push(1);
        assert_eq!(format!("{:?}", sw), "[3, 4, 1]");
        assert_eq!(sw.fold(), Some(8));
    }
    #[test]
    fn fold_not_commutative_works() {
        let mut sw = SWAg::<(i32, i32), _>::new(|(x, b), (y, c)| (c * x + y, b * c));
        sw.push((3, 10));
        sw.push((4, 10));
        sw.push((1, 10));
        assert_eq!(format!("{:?}", sw), "[(3, 10), (4, 10), (1, 10)]");
        assert_eq!(sw.fold(), Some((341, 1000)));
    }
    #[test]
    fn pop_works() {
        let mut sw = SWAg::<(i32, i32), _>::new(|(x, b), (y, c)| (c * x + y, b * c));
        sw.push((3, 10));
        sw.push((4, 10));
        sw.push((5, 10));
        sw.push((6, 10));
        assert_eq!(format!("{:?}", sw), "[(3, 10), (4, 10), (5, 10), (6, 10)]");
        assert_eq!(sw.pop(), Some((3, 10)));
        sw.push((1, 10));
        assert_eq!(format!("{:?}", sw), "[(4, 10), (5, 10), (6, 10), (1, 10)]");
        assert_eq!(sw.fold(), Some((4561, 10000)));
    }
}
