---
title: Kruskal
documentation_of: //lib/cpp/graphs/kruskal.hpp
---
## Brief
Kruskal 法。無向グラフに対し、全域を包囲できる木の最小コストを取得する。この時に作られる木を最小全域木という。

* constructor `Kruskal(n, m)`: 頂点数 `n`, 辺数 `m` で初期化。`m` は vector の reserve に使うだけなので `0` でも問題ないです。 $\Theta(1)$
* `add_edge(u, v, c)`: 頂点 `u`、`v` の間にコスト `c` の辺を張る。 $\Theta(1)$
* `build(builds_mst)`: MST の頂点数を返す (全域を包囲できたら `n` に一致)。`builds_mst` が `true` なら MST を構築する。 $O(m \log m)$

## Refs
* [クラスカル法による最小全域木を求めるアルゴリズム](https://algo-logic.info/kruskal-mst/), 634kami
