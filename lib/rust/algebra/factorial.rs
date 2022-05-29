// Factorial
//
// # Refs
// - https://github.com/akiradeveloper/rust-comp-snippets/blob/master/src/combination.rs
// - https://github.com/yosupo06/yosupo-library/blob/master/yosupo/comb.hpp
include!("modint.rs");

struct Factorial {
    n: usize,
    fact: Vec<Mint>,
    inv_fact: Vec<Mint>,
}
#[allow(dead_code)]
impl Factorial {
    fn new() -> Self {
        Self {
            n: 1,
            fact: vec![Mint::new_unchecked(1)],
            inv_fact: vec![Mint::new_unchecked(1)],
        }
    }
    fn expand(&mut self, mx: usize) {
        while self.n <= mx {
            self.fact.resize(self.n * 2, Mint::new_unchecked(0));
            for i in self.n..self.n * 2 {
                self.fact[i] = self.fact[i - 1] * Mint::new(i as i64);
            }
            self.inv_fact.resize(self.n * 2, Mint::new_unchecked(0));
            self.inv_fact[self.n * 2 - 1] = self.fact[self.n * 2 - 1].inv();
            for i in (self.n + 1..self.n * 2).rev() {
                self.inv_fact[i - 1] = self.inv_fact[i] * Mint::new(i as i64);
            }
            self.n *= 2;
        }
    }
    fn fact(&mut self, n: usize) -> Mint {
        self.expand(n);
        self.fact[n]
    }
    fn inv_fact(&mut self, n: usize) -> Mint {
        self.expand(n);
        self.inv_fact[n]
    }
    fn comb(&mut self, n: usize, r: usize) -> Mint {
        if n < r {
            Mint::new_unchecked(0)
        } else {
            self.fact(n) * self.inv_fact(r) * self.inv_fact(n - r)
        }
    }
    fn perm(&mut self, n: usize, r: usize) -> Mint {
        if n < r {
            Mint::new_unchecked(0)
        } else {
            self.fact(n) * self.inv_fact(n - r)
        }
    }
    fn homo(&mut self, n: usize, r: usize) -> Mint {
        self.comb(n + r - 1, r)
    }
}
