---
title: Square Matrix (正方行列の累乗)
documentation_of: //lib/cpp/algebra/square-matrix.hpp
---
## Brief
正方行列の累乗。

* constructor `SquareMatrix(n)`: `n` 行 `n` 列の行列を作り、全要素を $0$ で初期化。 $\Theta(n^2)$
* `pow(x)`: 行列累乗。 $\Theta(n^3 \log x)$
* `print()`: デバッグ用。 $\Theta(n^2)$

## Refs
* [https://ei1333.github.io/library/math/matrix/square-matrix.cpp](https://ei1333.github.io/library/math/matrix/square-matrix.cpp)
