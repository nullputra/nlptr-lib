---
title: Rerooting[op_edge] (全方位木 dp)
documentation_of: //lib/cpp/trees/rerooting-edge.hpp
---
## Brief
全方位木 dp のうち、辺に対して key を乗せて作用させるもの。

* `RerootingNode(n, id, merge, op_node)`: 初期化。 $\Theta(1)$
* `add_edge(u, v, k)`: 辺を追加。 $\Theta(1)$
* `add_edge(u, v, k1, k2)`: 辺を追加。 $\Theta(1)$
* `vals()`: 全方位 dp をして `_vals` を取得。 $O(\Theta(n))$

## Refs
* [もうひとつの全方位木DP](https://ei1333.hateblo.jp/entry/2018/12/21/004022), ei1333
