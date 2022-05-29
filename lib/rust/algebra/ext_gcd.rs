#[allow(dead_code)]
fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        // (a, b) = (b, a % b);
        let c = b;
        b = a % b;
        a = c;
    }
    a
}
#[allow(dead_code)]
fn lcm(a: i64, b: i64) -> i64 {
    if a == 0 && b == 0 {
        0
    } else {
        a / gcd(a, b) * b
    }
}
#[allow(dead_code)]
fn ext_gcd(a: i64, b: i64, x: &mut i64, y: &mut i64) -> i64 {
    let mut g = a;
    if b != 0 {
        g = ext_gcd(b, a % b, y, x);
        *y -= a / b * *x;
    } else {
        *x = 1;
        *y = 0;
    }
    g
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn gcd_lcm_works() {
        assert_eq!(gcd(0, 0), 0);
        assert_eq!(lcm(0, 0), 0);
        assert_eq!(gcd(6, 15), 3);
        assert_eq!(lcm(6, 15), 30);
        for x in 0..100 {
            assert_eq!(gcd(0, x), x);
        }
        for x in 0..100 {
            for y in 0..100 {
                assert_eq!(gcd(x, y) * lcm(x, y), x * y);
            }
        }
    }
}
