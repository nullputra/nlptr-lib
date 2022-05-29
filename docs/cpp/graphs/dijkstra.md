---
title: Dijkstra
documentation_of: //lib/cpp/graphs/dijkstra.hpp
---
## Brief
Dijkstra 法。正の辺のみからなる有向グラフに対し、ある始点から他の頂点への最短距離の配列を求める。

* constructor `Dijkstra(n、m)`: 頂点数 `n`、辺数 `m` で初期化。`m` は vector の reserve に使うだけなので $0$ でもよい。 $\Theta(1)$
* `add_edge(from, to, cost)`: 頂点 `from` から `to` に重み `cost` の有向辺を張る。 $\Theta(1)$
* `dists(s = 0)`: 始点 `s` から他の頂点への最短距離の配列を返す。 $O(n \log m)$
