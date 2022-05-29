const MOD: i64 = 998244353;
include!("modint.rs");

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn modint_998244353_works() {
        assert_eq!(mt(2).pow(10), mt(1024));
        assert_eq!(mt(283).pow(346), mt(401906323));

        // Fermat's little theorem
        for i in 2..100 {
            assert_eq!(mt(i).pow(MOD - 1), mt(1));
            // inverse element
            assert_eq!(mt(i).pow(MOD - 2), mt(1) / i);
        }
    }
}
