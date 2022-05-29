/// Mod Int
///
/// # Refs
/// - https://atcoder.jp/contests/typical90/submissions/24007424, kobae964
use std::fmt;
use std::ops::*;
pub trait Modulus: Copy {
    fn m() -> i64;
}
#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct ModInt<M> {
    pub x: i64,
    phantom: std::marker::PhantomData<M>,
}
#[allow(dead_code)]
impl<M: Modulus> ModInt<M> {
    pub fn new(mut x: i64) -> Self {
        x %= M::m();
        if x < 0 {
            x += M::m();
        }
        ModInt::new_unchecked(x)
    }
    fn new_unchecked(x: i64) -> Self {
        ModInt {
            x,
            phantom: std::marker::PhantomData,
        }
    }
    pub fn modulus() -> i64 {
        M::m()
    }
    #[must_use]
    pub fn pow(self, mut n: i64) -> Self {
        assert!(n >= 0);
        let mut res = ModInt::new_unchecked(1);
        let mut x = self;
        while n > 0 {
            if n % 2 != 0 {
                res *= x;
            }
            x *= x;
            n /= 2;
        }
        res
    }
    #[must_use]
    pub fn inv(self) -> Self {
        self.pow(M::m() - 2)
    }
}
impl<M: Modulus> Neg for ModInt<M> {
    type Output = Self;
    fn neg(self) -> Self {
        ModInt::new_unchecked(0) - self
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> Add<T> for ModInt<M> {
    type Output = Self;
    fn add(self, rhs: T) -> Self {
        let mut sum = self.x + rhs.into().x;
        if sum >= M::m() {
            sum -= M::m();
        }
        ModInt::new_unchecked(sum)
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> Sub<T> for ModInt<M> {
    type Output = Self;
    fn sub(self, rhs: T) -> Self {
        let mut sum = self.x - rhs.into().x;
        if sum < 0 {
            sum += M::m();
        }
        ModInt::new_unchecked(sum)
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> Mul<T> for ModInt<M> {
    type Output = Self;
    fn mul(self, rhs: T) -> Self {
        ModInt::new(self.x * rhs.into().x)
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> Div<T> for ModInt<M> {
    type Output = Self;
    #[allow(clippy::suspicious_arithmetic_impl)]
    fn div(self, rhs: T) -> Self {
        self * rhs.into().inv()
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> AddAssign<T> for ModInt<M> {
    fn add_assign(&mut self, rhs: T) {
        *self = *self + rhs;
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> SubAssign<T> for ModInt<M> {
    fn sub_assign(&mut self, rhs: T) {
        *self = *self - rhs;
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> MulAssign<T> for ModInt<M> {
    fn mul_assign(&mut self, rhs: T) {
        *self = *self * rhs;
    }
}
impl<M: Modulus, T: Into<ModInt<M>>> DivAssign<T> for ModInt<M> {
    fn div_assign(&mut self, rhs: T) {
        *self = *self / rhs;
    }
}
impl<M> fmt::Display for ModInt<M> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.x)
    }
}
impl<M> fmt::Debug for ModInt<M> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.x)
    }
}
impl<M: Modulus> From<i64> for ModInt<M> {
    fn from(x: i64) -> Self {
        Self::new(x)
    }
}
#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct P {}
impl Modulus for P {
    fn m() -> i64 {
        MOD
    }
}
type Mint = ModInt<P>;
#[allow(dead_code)]
fn mt(x: i64) -> Mint {
    Mint::new(x)
}
