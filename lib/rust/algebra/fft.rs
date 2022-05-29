// FFT
//
// # Refs
// - https://atcoder.jp/contests/typical90/submissions/24007424
include!("modint.rs");

#[allow(dead_code)]
mod fft {
    use std::ops::*;
    /// n: 2 冪, zeta: 原始 n 乗根
    #[inline(always)]
    pub fn transform<R>(f: &mut [R], zeta: R, one: R)
    where
        R: Copy + Add<Output = R> + Sub<Output = R> + Mul<Output = R>,
    {
        let n = f.len();
        assert!(n.is_power_of_two());
        let mut i = 0;
        for j in 1..n - 1 {
            let mut k = n >> 1;
            loop {
                i ^= k;
                if k <= i {
                    break;
                }
                k >>= 1;
            }
            if j < i {
                f.swap(i, j);
            }
        }
        let mut z_pw = {
            let mut z_pw = Vec::with_capacity(20);
            let mut m = 1;
            let mut cur = zeta;
            while m < n {
                z_pw.push(cur);
                cur = cur * cur;
                m *= 2;
            }
            z_pw
        };
        let mut m = 1;
        unsafe {
            while m < n {
                let base = z_pw.pop().unwrap();
                let mut r = 0;
                while r < n {
                    let mut w = one;
                    for s in r..r + m {
                        let &u = f.get_unchecked(s);
                        let d = *f.get_unchecked(s + m) * w;
                        *f.get_unchecked_mut(s) = u + d;
                        *f.get_unchecked_mut(s + m) = u - d;
                        w = w * base;
                    }
                    r += 2 * m;
                }
                m *= 2;
            }
        }
    }
}
#[allow(dead_code)]
fn conv(a: Vec<Mint>, b: Vec<Mint>) -> Vec<Mint> {
    let n = a.len() - 1;
    let m = b.len() - 1;
    let mut p = 1;
    while p <= n + m {
        p *= 2;
    }
    let mut f = vec![Mint::new_unchecked(0); p];
    let mut g = vec![Mint::new_unchecked(0); p];
    f[..=n].clone_from_slice(&a[..=n]);
    g[..=m].clone_from_slice(&b[..=m]);
    let fac = Mint::new(p as i64).inv();
    let zeta = Mint::new(3).pow((Mint::modulus() - 1) / p as i64);
    fft::transform(&mut f, zeta, Mint::new_unchecked(1));
    fft::transform(&mut g, zeta, Mint::new_unchecked(1));
    for i in 0..p {
        f[i] *= g[i] * fac;
    }
    fft::transform(&mut f, zeta.inv(), Mint::new_unchecked(1));
    f[..n + m + 1].to_vec()
}
