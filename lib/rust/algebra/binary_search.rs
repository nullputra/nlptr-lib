// # Refs
// - https://github.com/hatoo/competitive-rust-snippets/blob/master/src/binary_search.rs
pub trait BinarySearch<T> {
    fn lower_bound(&self, x: T) -> usize;
}
impl<T: Ord> BinarySearch<T> for [T] {
    fn lower_bound(&self, x: T) -> usize {
        let mut ng = -1isize;
        let mut ok = (self.len() - 1) as isize;
        while (ok - ng).abs() > 1 {
            let mid = (ok + ng) / 2;
            if x <= self[mid as usize] {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        ok as usize
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn lower_bound_works() {
        let n = 5;
        let a = vec![1, 5, 3, 2, 4];
        let mut dp = vec![std::usize::MAX; n];
        for &a in a.iter() {
            let idx = dp.lower_bound(a);
            dp[idx] = a;
        }
        let ans = dp.lower_bound(std::usize::MAX);
        assert_eq!(ans, 3);
    }
}
