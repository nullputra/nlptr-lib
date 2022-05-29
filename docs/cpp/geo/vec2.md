---
title: Vec2 (幾何)
documentation_of: //lib/cpp/geo/vec2.hpp
---
## Brief
幾何ライブラリです。事前に `using V2 = Vec2<double>;` や `using V2 = Vec2<int>;` をして使ってください。

* `manhattan_dis(v1, v2)`
* `inter_seg_pt(a1, a2, b)`:
  3 点の位置関係を返す関数。(`A` $\neq$ `B` であることが必要)
  - `AB` から見て `BC` は右に曲がる (つまり 右回り): $-1$
  - `AB` から見て `BC` は左に曲がる (つまり 左回り): $+1$
  - `CAB` の順番で一直線上に並ぶ: `-2`
  - `ABC` の順番で一直線上に並ぶ: `+2`
  - `BCA` の順番で一直線上に並ぶ: `0`
* `angle(a, b, c)`: 角 `ABC` を返す。
* `angle_type(a, b, c)`: 角 `ABC` が鋭角なら $-1$、直角なら $0$、鈍角なら $1$ を返す。
* `intersect_type(a1, a2, b1, b2)`: 並行なら $0$、交わっていれば $1$、一致で $2$. `A`、`B`: 直線.
* `is_intersect_seg(a1, a2, b1, b2)`: `A`、`B`: 線分。
* `is_intersect_seg_ray(a1, a2, b, b_arg)`: `A`: 線分、`B`: 半直線(ray)。
* `intersection(a1, a2, b1, b2)`: 交点の座標を求める。`A`, `B`: 直線。
* `dis(a, b, p)`: 直線 `AB` と点 `P` の距離。
* `area_triangle(a, b)`: 三角形 OAB の面積を求める (`O`: 原点)。正号: `O`、`A`、`B` が左回り、負号: `O`、`A`、`B` が右回り。
* `area_polygon(p)`: 正号: `O`、`A`、`B`、 $\cdots$ が左回り, 負号: `O`、`A`、`B`、 $\cdots$ が右回り。
* `center_of_grav_polygon(p)`: 重心の座標。
* `convex_hull`: 凸包を形成する頂点の配列を返す。すなわち、外から輪ゴムを付けたとき、輪ゴムと接する頂点の配列を返す。 $O(n \log n)$

## Refs
* [Vec2 クラスを作る（モダンな C++ クラスデザインのためのチュートリアル）](https://qiita.com/Reputeless/items/96226cfe1282a014b147), Ryo Suzuki
* [２．計算幾何のインフラ整備　　　シリーズ：「基礎的計算幾何ライブラリの作り方」](https://sen-comp.hatenablog.com/entry/2020/03/12/145742), Sen
* [プログラミングコンテストにおける計算幾何入門](https://www.ioi-jp.org/camp/2017/2017-sp_camp-hide.pdf), 秀 郁未
