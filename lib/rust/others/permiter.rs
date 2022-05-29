/// Perm Iter
///
/// # Refs
/// - https://blog.tiqwab.com/2021/08/01/permutation-iterator-rust.html, tiqwab
struct PermIter<T: Ord + Clone> {
    li: Vec<T>,
    finished: bool,
}
impl<T: Ord + Clone> PermIter<T> {
    fn new(mut li: Vec<T>) -> PermIter<T> {
        let finished = li.is_empty();
        li.sort();
        PermIter { li, finished }
    }
}
impl<T: Ord + Clone> Iterator for PermIter<T> {
    type Item = Vec<T>;
    fn next(&mut self) -> Option<Self::Item> {
        if self.finished {
            return None;
        }
        if self.li.len() == 1 {
            self.finished = true;
            return Some(self.li.clone());
        }
        let mut i = self.li.len() - 1;
        let res = self.li.clone();
        loop {
            let ii = i;
            i -= 1;
            if self.li[i] < self.li[ii] {
                let mut j = self.li.len() - 1;
                while self.li[i] >= self.li[j] {
                    j -= 1;
                }

                self.li.swap(i, j);
                self.li[ii..].reverse();
                return Some(res);
            }
            if i == 0 {
                self.li.reverse();
                self.finished = true;
                return Some(res);
            }
        }
    }
}
trait Permutation<T: Ord + Clone> {
    fn permutation(self) -> PermIter<T>;
}
impl<T: Ord + Clone, I: IntoIterator<Item = T>> Permutation<T> for I {
    fn permutation(self) -> PermIter<T> {
        PermIter::new(self.into_iter().collect())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn permiter_works() {
        let ans = [
            vec![1, 2, 3],
            vec![1, 3, 2],
            vec![2, 1, 3],
            vec![2, 3, 1],
            vec![3, 1, 2],
            vec![3, 2, 1],
        ];
        for (i, a) in [1, 2, 3].permutation().enumerate() {
            assert_eq!(ans[i], a);
        }
    }
}
