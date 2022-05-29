---
title: Segment Tree (遅延評価セグメント木)
documentation_of: //lib/cpp/data-structures/segment-tree.hpp
---
## Brief
* constructor `SegmentTree<V, T>(vals, _ev, _fv, _et, _ft, _fm)`: `init(vals)` を呼ぶ。
* `init(vals)`: 初期化。
* `apply(t, l, r = -1)`: $[l,r)$ に `t` を作用する。
* `leftmost(l, f)`: $val[l:]$ において境界の最左位置。
* `rightmost(r, f)`: $val[:r]$ において境界の最右位置。
* `prod(l, r)`: $f[l,r)$ を返す。

## Refs
* [AtCoder LibraryのLazy Segtreeのチートシート](https://betrue12.hateblo.jp/entry/2020/09/23/005940), betrue12
* [https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp), yosupo
