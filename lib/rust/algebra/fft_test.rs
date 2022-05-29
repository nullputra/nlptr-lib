const MOD: i64 = 998244353;
include!("fft.rs");

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn atc_fft_c() {
        // https://atcoder.jp/contests/atc001/tasks/fft_c
        let vmt = |v: Vec<i64>| {
            let mut res = Vec::<Mint>::new();
            for &v in v.iter() {
                res.push(mt(v));
            }
            res
        };

        let a = vmt(vec![1, 2, 3, 4]);
        let b = vmt(vec![1, 2, 4, 8]);

        // [1, 4, 11, 26, 36, 40, 32]
        let mut c = conv(a, b);
        // [0, 1, 4, 11, 26, 36, 40, 32]
        c.insert(0, mt(0));

        let model_ans = vmt(vec![0, 1, 4, 11, 26, 36, 40, 32]);
        assert_eq!(c, model_ans);
    }
}
