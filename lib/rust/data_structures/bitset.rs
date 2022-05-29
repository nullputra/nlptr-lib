/// BitSet
///
/// # Refs
/// - https://github.com/hatoo/competitive-rust-snippets/blob/master/src/bitset.rs, hatoo
#[derive(Clone)]
struct BitSet {
    n: usize,
    buf: Vec<u128>,
}
#[allow(dead_code)]
impl BitSet {
    fn new(n: usize) -> BitSet {
        BitSet {
            n,
            buf: vec![0; (n + 127) / 128],
        }
    }
    fn set(&mut self, i: usize, b: bool) {
        assert!(i < self.n);
        if b {
            self.buf[i >> 7] |= 1 << (i & 127);
        } else {
            self.buf[i >> 7] &= !(1 << (i & 127));
        }
    }
    fn count_ones(&self) -> u32 {
        self.buf.iter().map(|x| x.count_ones()).sum()
    }
    fn chomp(&mut self) {
        let r = self.n & 127;
        if r != 0 {
            if let Some(x) = self.buf.last_mut() {
                let d = 128 - r;
                *x = (*x << d) >> d;
            }
        }
    }
}
impl std::ops::Index<usize> for BitSet {
    type Output = bool;
    fn index(&self, index: usize) -> &bool {
        if self.buf[index >> 7] >> (index & 127) & 1 == 1 {
            &true
        } else {
            &false
        }
    }
}
impl std::ops::ShlAssign<usize> for BitSet {
    fn shl_assign(&mut self, x: usize) {
        let q = x >> 7;
        let r = x & 127;
        if q >= self.buf.len() {
            for x in &mut self.buf {
                *x = 0;
            }
            return;
        }
        if r == 0 {
            for i in (q..self.buf.len()).rev() {
                self.buf[i] = self.buf[i - q];
            }
        } else {
            for i in (q + 1..self.buf.len()).rev() {
                self.buf[i] = (self.buf[i - q] << r) | (self.buf[i - q - 1] >> (128 - r));
            }
            self.buf[q] = self.buf[0] << r;
        }
        for x in &mut self.buf[..q] {
            *x = 0;
        }
        self.chomp();
    }
}
impl std::ops::Shl<usize> for BitSet {
    type Output = Self;
    fn shl(mut self, x: usize) -> Self {
        self <<= x;
        self
    }
}
impl std::ops::ShrAssign<usize> for BitSet {
    fn shr_assign(&mut self, x: usize) {
        let q = x >> 7;
        let r = x & 127;
        if q >= self.buf.len() {
            for x in &mut self.buf {
                *x = 0;
            }
            return;
        }
        if r == 0 {
            for i in 0..self.buf.len() - q {
                self.buf[i] = self.buf[i + q];
            }
        } else {
            for i in 0..self.buf.len() - q - 1 {
                self.buf[i] = (self.buf[i + q] >> r) | (self.buf[i + q + 1] << (128 - r));
            }
            let len = self.buf.len();
            self.buf[len - q - 1] = self.buf[len - 1] >> r;
        }
        let len = self.buf.len();
        for x in &mut self.buf[len - q..] {
            *x = 0;
        }
    }
}
impl std::ops::Shr<usize> for BitSet {
    type Output = Self;
    fn shr(mut self, x: usize) -> Self {
        self >>= x;
        self
    }
}
impl<'a> std::ops::BitAndAssign<&'a BitSet> for BitSet {
    fn bitand_assign(&mut self, rhs: &'a Self) {
        for (a, b) in self.buf.iter_mut().zip(rhs.buf.iter()) {
            *a &= *b;
        }
    }
}
impl<'a> std::ops::BitAnd<&'a BitSet> for BitSet {
    type Output = Self;
    fn bitand(mut self, rhs: &'a Self) -> Self {
        self &= rhs;
        self
    }
}
impl<'a> std::ops::BitOrAssign<&'a BitSet> for BitSet {
    fn bitor_assign(&mut self, rhs: &'a Self) {
        for (a, b) in self.buf.iter_mut().zip(rhs.buf.iter()) {
            *a |= *b;
        }
        self.chomp();
    }
}
impl<'a> std::ops::BitOr<&'a BitSet> for BitSet {
    type Output = Self;
    fn bitor(mut self, rhs: &'a Self) -> Self {
        self |= rhs;
        self
    }
}
impl<'a> std::ops::BitXorAssign<&'a BitSet> for BitSet {
    fn bitxor_assign(&mut self, rhs: &'a Self) {
        for (a, b) in self.buf.iter_mut().zip(rhs.buf.iter()) {
            *a ^= *b;
        }
        self.chomp();
    }
}
impl<'a> std::ops::BitXor<&'a BitSet> for BitSet {
    type Output = Self;
    fn bitxor(mut self, rhs: &'a Self) -> Self {
        self ^= rhs;
        self
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn abc204_d() {
        // ABC204 D - Cooking https://atcoder.jp/contests/abc204/tasks/abc204_d
        // BitSet による 128 倍高速化
        let solve = |t: Vec<usize>| {
            let mut sum = 0;
            let mut bt = BitSet::new(100020);
            bt.set(0, true);
            for &t in t.iter() {
                bt = bt.clone() | &(bt << t);
                sum += t;
            }
            let mut ans = sum;
            for i in (sum + 1) / 2..=sum {
                if bt[i] {
                    ans = i;
                    break;
                }
            }
            ans
        };
        assert_eq!(solve(vec![8, 3, 7, 2, 5]), 13);
        assert_eq!(solve(vec![1000, 1]), 1000);
        assert_eq!(solve(vec![3, 14, 15, 9, 26, 5, 35, 89, 79]), 138);
    }
}
