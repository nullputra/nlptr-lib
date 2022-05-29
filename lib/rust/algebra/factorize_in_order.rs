struct FactorizeInOrder {
    n: usize,
    min_factors: Vec<usize>,
}
#[allow(dead_code)]
impl FactorizeInOrder {
    fn new(n: usize) -> FactorizeInOrder {
        let mut min_factors = (0..=n).collect::<Vec<usize>>();
        for i in 2..=(n as f32).sqrt().ceil() as usize {
            if min_factors[i] != i {
                continue;
            }
            for j in i..=n / i {
                if min_factors[i * j] == i * j {
                    min_factors[i * j] = i;
                }
            }
        }
        FactorizeInOrder { n, min_factors }
    }
    fn factors(&self, x: usize) -> Vec<(usize, usize)> {
        assert!(0 < x && x <= self.n);
        if x == 1 {
            return vec![];
        }
        let mut x = x;
        let mut facts = vec![];
        let mut cur = self.min_factors[x];
        let mut ex = 0;
        loop {
            if cur != self.min_factors[x] {
                facts.push((cur, ex));
                if x == 1 {
                    break;
                }
                cur = self.min_factors[x];
                ex = 0;
            }
            ex += 1;
            x /= self.min_factors[x];
        }
        facts
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn factors_works() {
        let sv = FactorizeInOrder::new(96500);
        assert_eq!(sv.factors(1), []);
        assert_eq!(sv.factors(57), [(3, 1), (19, 1)]);
        assert_eq!(sv.factors(2022), [(2, 1), (3, 1), (337, 1)]);
        assert_eq!(sv.factors(2357), [(2357, 1)]);
        assert_eq!(sv.factors(96500), [(2, 2), (5, 3), (193, 1)]);
    }
    #[test]
    fn min_factors_works() {
        let sv = FactorizeInOrder::new(100);
        assert_eq!(
            sv.min_factors,
            [
                0, 1, 2, 3, 2, 5, 2, 7, 2, 3, 2, 11, 2, 13, 2, 3, 2, 17, 2, 19, 2, 3, 2, 23, 2, 5,
                2, 3, 2, 29, 2, 31, 2, 3, 2, 5, 2, 37, 2, 3, 2, 41, 2, 43, 2, 3, 2, 47, 2, 7, 2, 3,
                2, 53, 2, 5, 2, 3, 2, 59, 2, 61, 2, 3, 2, 5, 2, 67, 2, 3, 2, 71, 2, 73, 2, 3, 2, 7,
                2, 79, 2, 3, 2, 83, 2, 5, 2, 3, 2, 89, 2, 7, 2, 3, 2, 5, 2, 97, 2, 3, 2
            ]
        );
    }
}
