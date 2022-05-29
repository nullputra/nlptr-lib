---
title: Rerooting[op_node] (全方位木 dp)
documentation_of: //lib/cpp/trees/rerooting-node.hpp
---
## Brief
全方位木 dp のうち、頂点に対して作用するもの。

* `RerootingNode(n, id, merge, op_node)`
* `add_edge(u, v)`: 辺を追加する。 $\Theta(1)$
* `vals()`: 全方位 dp をして `_vals` を返す。 $\Theta(n)$

## Refs
* [【全方位木DP】明日使える便利な木構造のアルゴリズム](https://qiita.com/keymoon/items/2a52f1b0fb7ef67fb89e), keymoon
