---
title: Factorial (階乗、組み合わせ)
documentation_of: //lib/cpp/algebra/factorial.hpp
---
## Brief
階乗系列の関数。階乗などの配列の用意すべきサイズの指定が不要で、必要に応じ自動で増築されます。

* `fact(n)`: $n!$ を返す。ならし $\Theta(1)$
* `inv_fact(n)`: $\frac{1}{n!}$ を返す。ならし $\Theta(1)$
* `comb(n, r)`: $_nC_r$ を返す。ならし $\Theta(1)$
* `perm(n, r)`: $_nP_r$ を返す。ならし $\Theta(1)$
* `homo(n, r)`: $_nH_r$ を返す。ならし $\Theta(1)$
* `catalan(n)`: カタラン数 $c_n = \frac{_{2n}C_n}{n+1}$ を返す。ならし $\Theta(1)$<br>
  e.g. $n=0,1,2, ...$ に対して $c_n$ は $1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, \cdots$ となる。
  - カタラン数の表現。
    1. 漸化式 $c_0 = 1, c_{n+1} = \sum_{i=0}^{n} c_i c_{n-i}$ を満たす数列 $c_n$
    2. 縦横 $n$ マスの格子において左下から右上まで対角線をまたがずに行く（踏むのは ok）最短経路の数 $c_n$
* `inv(n, r)`: $\frac{1}{n}$ を返す。ならし $\Theta(1)$

* `0_M` で `mint(0)` を表現できます (`std::accumulate` の第三引数などで使う)。

## Refs
* [https://github.com/yosupo06/yosupo-library/blob/master/yosupo/comb.hpp](https://github.com/yosupo06/yosupo-library/blob/master/yosupo/comb.hpp), yosupo
* [https://github.com/tatyam-prime/kyopro_library/blob/master/Modint.cpp](https://github.com/tatyam-prime/kyopro_library/blob/master/Modint.cpp), tatyam
* [カタラン数の意味と漸化式 - 高校数学の美しい物語](https://manabitimes.jp/math/657), マスオ
