#[allow(dead_code)]
fn factors(n: i64) -> Vec<(i64, i64)> {
    let mut n = n;
    let mut facts = vec![];
    for a in 2..=(n as f64).sqrt().ceil() as i64 {
        let mut ex = 0;
        while n % a == 0 {
            n /= a;
            ex += 1;
        }
        if ex > 0 {
            facts.push((a, ex));
        }
        if n == 1 {
            break;
        }
    }
    if n != 1 {
        facts.push((n, 1));
    }
    facts
}
#[allow(dead_code)]
fn divisors(n: i64) -> Vec<i64> {
    let mut divs = vec![];
    for i in 1..=(n as f64).sqrt() as i64 {
        if n % i == 0 {
            divs.push(i);
            if i != n / i {
                divs.push(n / i);
            }
        }
    }
    divs.sort_unstable();
    divs
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn factors_works() {
        assert_eq!(factors(36), [(2, 2), (3, 2)]);
        assert_eq!(factors(121), [(11, 2)]);
        assert_eq!(factors(998244353), [(998244353, 1)]);
    }
    #[test]
    fn divisors_works() {
        assert_eq!(divisors(36), [1, 2, 3, 4, 6, 9, 12, 18, 36]);
        assert_eq!(divisors(121), [1, 11, 121]);
        assert_eq!(divisors(998244353), [1, 998244353]);
    }
}
