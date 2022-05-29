---
title: Cumulative Sum 2d (二次元累積和)
documentation_of: //lib/cpp/data-structures/cumulative-sum-2d.hpp
---
## Brief
* constructor `CumulativeSum2d<T, is_rect_addition>(h, w)`: `is_rect_addition` が `true` なら矩形加算・点取得、`false` なら点加算・矩形和取得。
* `is_rect_addition` == `true` のとき。
  - `add(y1, x1, y2, x2, a)`: 矩形 $[y_1, y_2) \times [x_1, x_2)$ に $a$ を加算。
  - `get(y, x)`: 点 $(y, x)$ の値を返す。
* `is_rect_addition` == `false` のとき。
  - `add(y, x, a)`: 点 $(y, x)$ に $a$ を加算。
  - `get(y1, x1, y2, x2)`: 矩形 $[y_1, x_1) \times [y_2, x_2)$ の総和を返す。
* `print(prints_prev)`: デバッグ用。

## Refs
* [https://ei1333.github.io/luzhiled/snippets/dp/slide-min.html](https://ei1333.github.io/luzhiled/snippets/dp/slide-min.html), ei1333
