---
title: Number Theoretic Transform (NTT、数論変換)
documentation_of: //lib/cpp/conv/number-theoretic-transform.hpp
---
## Brief
数論変換。

* `NumberTheoreticTransform<m>()`: 法を `m` とする。
  有効な素数 `m` の候補を 3 つ挙げれば、
  - $924844033 = 2^{21} \times 3^2 \times 7^2 + 1$
  - $998244353 = 2^{23} \times 119 + 1$
  - $1012924417 = 2^{21} \times 3 \times 7 \times 23 + 1$
* `ntt(f)`: $f \to F$ 。
* `conv(f, g, is_square)`: 関数 `f`、`g` を畳み込んで得た `h` を返す。`f` == `g` なら `is_square` で高速化できる。`i` 円の主菜と副菜で `k` 円定食を作る作り方。

## Refs
* [https://ei1333.github.io/library/math/fft/number-theoretic-transform.cpp](https://ei1333.github.io/library/math/fft/number-theoretic-transform.cpp), ei1333
* [FFTとNTTとFMTと](https://qiita.com/peria/items/f6912f6d91db409ca87a), Peria
* [NTT(数論変換)のやさしい解説](https://qiita.com/Sen_comp/items/9401382df736e51564c1), Sen_comp
