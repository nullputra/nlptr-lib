use std::fmt;
use std::ops::*;
#[derive(Eq, PartialEq)]
struct Rational {
    n: i64,
    d: i64,
}
impl Rational {
    fn new(mut n: i64, mut d: i64) -> Self {
        assert!(d != 0, "Zero is an invalid denominator!");
        let g = gcd(n, d);
        n /= g;
        d /= g;
        Self { n, d }
    }
}
impl Add for Rational {
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        let mut n = self.n;
        let mut d = self.d;
        let g = gcd(d, rhs.d);
        d /= g;
        n = n * (rhs.d / g) + rhs.n * d;
        let g = gcd(n, g);
        Self::new(n / g, d * (rhs.d / g))
    }
}
impl Sub for Rational {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        let mut n = self.n;
        let mut d = self.d;
        let g = gcd(d, rhs.d);
        d /= g;
        n = n * (rhs.d / g) - rhs.n * d;
        let g = gcd(n, g);
        Self::new(n / g, d * (rhs.d / g))
    }
}
impl Mul for Rational {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self {
        Self::new(self.n * rhs.n, self.d * rhs.d)
    }
}
impl Div for Rational {
    type Output = Self;
    fn div(self, rhs: Self) -> Self {
        Self::new(self.n * rhs.d, self.d * rhs.n)
    }
}
impl fmt::Display for Rational {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}/{}", self.n, self.d)
    }
}
impl fmt::Debug for Rational {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}/{}", self.n, self.d)
    }
}
fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        // (a, b) = (b, a % b);
        let c = b;
        b = a % b;
        a = c;
    }
    a
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn rational_works() {
        let rl = Rational::new;
        assert_eq!(rl(1, 2), rl(2, 4));
        assert_eq!(rl(1, 2) + rl(1, 3), rl(5, 6));
        assert_eq!(rl(1, 3) - rl(1, 5), rl(2, 15));
        assert_eq!(rl(2, 3) * rl(3, 4), rl(1, 2));
        assert_eq!(rl(2, 3) / rl(3, 4), rl(8, 9));

        // fmt::Display
        assert_eq!(format!("{}", rl(283, 1)), "283/1");
        // fmt::Debug
        assert_eq!(format!("{:?}", rl(346, 765)), "346/765");
    }
}
