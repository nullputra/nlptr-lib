---
title: Linear Sieve (線形篩、添え字 gcd 畳み込み)
documentation_of: //lib/cpp/algebra/linear-sieve.hpp
---
## Brief
線形篩・最小素因数(`min_factors`)・GCD 畳み込みの相性がいいことを見つけたので作りました。できることは以下の二つです。
* 前計算による高速素因数分解 $O(d(x))$
* GCD 畳み込み $O(\pi(x))$

また、計算量表記において、
* $d(x) := (x の持つ約数の個数) = O(\sqrt{x})$
* $\pi(x) := (x 以下である素数の個数) = O(\frac{x}{\log x})$

を用います。

* constructor `LinearSieve(n, calcs_mob)`: 素因数分解する自然数の最大値を `n`、メビウス関数値の配列 `mob` を構築するかを `calcs_mob` として指定。線形篩により `min_factors`、`primes` を構築する。なお、`min_factors[x]` $:= (整数 x の持つ最小の素因数)$ です。 $\Theta(n)$
* `factorize(x)`: 線形篩で前計算した `min_factors` を用いた自然数 `x` の素因数分解の結果を返す。int でオーバーフローしない範囲のみ対応。 $O(d(x))$  
  e.g. `7007 -> [(7, 2), (11, 1), (13, 1)]`
* `divisors(x, sorted)`: `factorize(x)` を用いて求めた自然数 `x` の約数の配列を返す。`sorted` が false のときは未ソートで返す。 $O(d(x))$
* `f1(F)`: `mob` を用いて計算して `mobius(F)[1]` を返す。 $O(m)$ (ただし $m := |F|$)
* `zeta(f)`: `primes` を用いて、約数系の高速 zeta 変換を行う。 $O(\pi(m))$ (ただし $m := |f|$)
* `mobius(F)`: `primes` を用いて、約数系の高速 mobius 変換を行う。 $O(\pi(m))$ (ただし $m := |F|$)
* `gcd_conv(f, g)`: 関数 `f`、`g` を添え字 GCD 畳み込みして得た `h` を返す。 $O(\pi(m))$ (ただし $m := max(|f|, |g|)$)  
  e.g. `f: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]、g: [0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23]` のとき  
  `h: [0, 6336, 1670, 915, 684, 230, 336, 91, 120, 153, 190, 231, 276]` となる。

## Refs
### 線形篩
* [【競プロ】数学メモ](https://kanpurin.hatenablog.com/entry/2021/08/14/115825), kanpurin

### 添え字 gcd 畳み込み
* [AtCoder AGC 038 C - LCMs (黄色, 700 点)](https://drken1215.hatenablog.com/entry/2020/11/06/031600), drken
* [添え字 gcd での畳み込みで AGC038-C を解く](https://noshi91.hatenablog.com/entry/2019/09/23/002445), noshi91

### 素数の個数の上からの評価
* [素数に関する上からの評価（初等的な証明）](https://maspypy.com/%E7%B4%A0%E6%95%B0%E3%81%AB%E9%96%A2%E3%81%99%E3%82%8B%E4%B8%8A%E3%81%8B%E3%82%89%E3%81%AE%E8%A9%95%E4%BE%A1%EF%BC%88%E5%88%9D%E7%AD%89%E7%9A%84%E3%81%AA%E8%A8%BC%E6%98%8E%EF%BC%89), maspy
