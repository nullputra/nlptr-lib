---
title: Modular (剰余環上の型)
documentation_of: //lib/cpp/algebra/modular.hpp
---
## Brief
自動で mod を取る構造体。

## Usage
```cpp
// #include の上に const int MOD = 1e9 + 7; や
// const int MOD = 998244353; を書いてから使ってください。
const int MOD = 1e9 + 7;
#include "algebra/modular.hpp"
int main() {
    mint ans = 0;
    // (中略)
    return 0;
}
```

## Complexity
* 演算:
  - 割り算: $O(\log n)$
  - 割り算以外: $O(1)$
* `mod()`: $O(1)$
* `val()`: $O(1)$
* `pow(n)`: $O(\log n)$
* `inv()`: $O(\log MOD)$

## Refs
* [https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/modint.hpp)
