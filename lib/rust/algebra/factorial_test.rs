const MOD: i64 = 998244353;
include!("factorial.rs");

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn factorial_works() {
        // 階乗 n! として使う最大の n を指定しない.
        // 足りなくなったらリサイズされる.
        let mut ft = Factorial::new();

        // (5 * 4) / (2 * 1)
        assert_eq!(ft.comb(5, 2), mt(10));
        // 5 * 4 * 3
        assert_eq!(ft.perm(5, 3), mt(60));

        // Ref: 重複組み合わせ http://yosshy.sansu.org/chofuku.htm, ヨッシーの算数・数学の部屋
        // homo(3, 3) = comb(3 + 3 - 1, 3)
        assert_eq!(ft.homo(3, 3), mt(10));
        // homo(7, 2) = comb(7 + 2 - 1, 2)
        assert_eq!(ft.homo(7, 2), mt(28));
    }
}
