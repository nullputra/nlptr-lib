---
title: Slope Trick
documentation_of: //lib/cpp/data-structures/slope-trick.hpp
---
## Brief
どの傾きも整数である区分線形凸関数 $f(x)$ を効率的に扱う。以下 $n = (関数 f の傾きの変化点の個数)$ とする。

1. 内部実装について。

  - `priority_queue<T> ql;`: `x < get_min_x()` なる $x$ の max。
  - `priority_queue<T, vector<T>, greater<T>> qr;`: `x > get_min_x()` なる $x$ の min。

2. public な constructor・関数について。

  * constructor `SlopeTrick<T>()`
  * `clear_l()`: `ql` を全削除。右側累積 min をする。
  * `clear_r()`: `qr` を全削除。左側累積 min をする。
  * `add_a_minus_x(a)`: $f(x) += a-x$ とする。
  * `add_x_minus_a(a)`: $f(x) += x-a$ とする。
  * `add_ab_x_minus_a(a)`: $f(x) += |x-a|$ とする。
  * `shift_x(x)`: $x += a$ (i.e. $f(x) \to f(x - a)$ ) とする。
  * `shift_y(y)`: $f(x) += a$ とする。
  * `shift_l(l)`: スライド最小値関数。左側のみ `shift_x(l)` する。
  * `shift_r(r)`: スライド最小値関数。右側のみ `shift_x(r)` する。
  * `get_min_y()`: $min(f(x))$ を返す。
  * `get_min_x()`: $f(x)$ が最小値を取るような $x$ を返す。
  * `get_fx(x)`: $f(x)$ を返す。副作用: `ql`、`qr` を破壊する。
  * `merge(st)`: 副作用: `st` を破壊する。

## Refs
* [https://ei1333.github.io/library/structure/others/slope-trick.cpp](https://ei1333.github.io/library/structure/others/slope-trick.cpp), ei1333
* [slope trick (1) 解説編](https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8), maspy
