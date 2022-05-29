---
title: SWAG (Sliding Window Aggregation)
documentation_of: //lib/cpp/data-structures/swag.hpp
---
## Brief
半群の元からなる列 $\boldsymbol a = a_0, a_1, \cdots, a_{n-1}$ を扱う。Sparse Table は SWAG で置き換えられることがある。

* constructor `SWAG<T>(op, id)`: 型 $T$、演算 $op$、単位元 $id$ で初期化。 $\Theta(1)$
* `push(x)`: $\boldsymbol a$ の末尾に要素 $x$ を追加する。 $\Theta(1)$
* `pop()`: $\boldsymbol a$ の先頭にある要素 $a_0$ を削除する。`fold()` を返す。 $\Theta(1)$
* `fold()`: $\boldsymbol a$ の要素の総積 $a_0 \cdot a_1 \cdot \: \cdots \: \cdot a_{n-1}$ を返す。ならし $\Theta(1)$

## Usage
```cpp
#include "data-structures/swag.hpp"
using ll = long long;
ll op(ll x, ll y) { return max(x, y); };
int main() {
    const ll id = -1e18;
    using SW = SWAG<ll, op, id>;
    SW sw;
}
```

## Refs
* [https://github.com/tatyam-prime/kyopro_library/blob/master/SWAG.cpp](https://github.com/tatyam-prime/kyopro_library/blob/master/SWAG.cpp), tatyam
* [SWAG(Sliding Window Aggregation)再考](https://motsu-xe.hatenablog.com/entry/2021/05/13/224016), Motsu_xe
