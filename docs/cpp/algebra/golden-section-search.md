---
title: Golden Section Search (黄金分割探索)
documentation_of: //lib/cpp/algebra/golden-section-search.hpp
---
## Brief
黄金分割探索 (三分探索の一つ)。単峰関数の大域最大値 (大域最小値) を求める。二分探索はライブラリ化するまでもないが、(黄金分割探索も含めて) 三分探索は `is_convex_upward` が `true` か否かにより実装が少し変わるのでライブラリ化しておくと便利。

* `golden_section_search(l_lim, r_lim, f, is_convex_upward)`: 関数 $y = f(x)$ において大域最大値 (大域最小値) を取るような $x$ を求め、$\{x, f(x)\}$ を返す。`is_convex_upward` については $f$ が上に凸なら `true`、下に凸なら `false` を指定。

## Refs
* [三分探索と黄金分割探索](https://naoyat.hatenablog.jp/entry/2012/01/04/231801), naoya_t
