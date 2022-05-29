---
title: Fast Fourier Transform (FFT、高速フーリエ変換)
documentation_of: //lib/cpp/conv/fast-fourier-transform.hpp
---
## Brief
* struct `Angles`: `ang[i] = (360° / 2^(i+1))` としています。
* `fft(f, is_inverse)`: `is_inverse` が `true` なら $f \to F$、そうでないなら $F \to f$。
* `conv(f, g, is_square)`: 関数 `f`、`g` を畳み込んで得た `h` を返す。`f` == `g` なら `is_square` に `true` を指定することで高速化できる。`i` 円の主菜と副菜で `k` 円定食を作る作り方。

## Refs
* [https://ei1333.github.io/library/math/fft/fast-fourier-transform.cpp](https://ei1333.github.io/library/math/fft/fast-fourier-transform.cpp), ei1333
* [FFT（高速フーリエ変換）を完全に理解する話](https://qiita.com/ageprocpp/items/0d63d4ed80de4a35fe79), kaage
