---
title: Formal Power Series (形式的冪級数)
documentation_of: //lib/cpp/algebra/formal-power-series.hpp
---
## Brief
* constructor `FPS(v)`: `v` で初期化。
* constructor `FPS(list)`: `list` で初期化。
* `integral()`: $\int f(x)$ を返す (表している関数を $f$ とした)。
* `eval(x)`: $f(x)$ を返す。

## Usage
```cpp
const int MOD = 1e9 + 7;
#include "algebra/formal-power-series.hpp"
vector<mint> a(n, 2);
FPS f(a);
f *= FPS{2};
```

## Refs
* [https://github.com/yosupo06/yosupo-library/blob/master/yosupo/fps.hpp](https://github.com/yosupo06/yosupo-library/blob/master/yosupo/fps.hpp), yosupo
* ([形式的冪級数（FPS）の inv，log，exp，pow の定数倍の軽いアルゴリズム](https://opt-cp.com/fps-fast-algorithms/), opt)
