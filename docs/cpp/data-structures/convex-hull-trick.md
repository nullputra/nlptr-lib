---
title: Convex Hull Trick
documentation_of: //lib/cpp/data-structures/convex-hull-trick.hpp
---
## Brief
直線 (一次関数) 群の y の最小値を求める。dp の漸化式を整理したときなどに、$\min(a_i x + b_i)$ の形の式になるとき Convex Hull Trick を使えることがある。add query にて、a が単調非増加 (減少) の状況でのみ使える。

* constructor `ConvexHullTrick<T>(a_incr)`: `a` が昇順となるように add query していくなら `true`、降順で add query するなら `false` を指定。
* `add(a, b)`: 直線 $y = ax + b$ を追加。
* `get(x)`: 単調性のため二分探索できる。 $O((n+q) \log n)$
* `get_x_incr(x)`: get query の `x` までも単調なら使える。 $O(n+q)$
* (参考) private `necessary(p1, p2, p3)`:<br>
  交点の x 座標の比較により、直線 $P_3$ が必要かどうかを評価する。  
  $(P_1, P_2 の交点の x 座標) < (P_2, P_3 の交点の x 座標) \Leftrightarrow \frac{b_2 - b_1}{a_1 - a_2} < \frac{b_3 - b_2}{a_2 - a_3}$

## Refs
* [Convex-Hull Trick - sataniC++](https://satanic0258.hatenablog.com/entry/2016/08/16/181331), satanic0258
* [https://ei1333.github.io/library/structure/convex-hull-trick/convex-hull-trick-add-monotone.cpp](https://ei1333.github.io/library/structure/convex-hull-trick/convex-hull-trick-add-monotone.cpp), ei1333
