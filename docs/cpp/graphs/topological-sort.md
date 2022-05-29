---
title: Topological Sort
documentation_of: //lib/cpp/graphs/topological-sort.hpp
---
## Brief
DAG (directed acyclic graph、有向非巡回グラフ) の各ノードを順序付けして、どのノードもその出力辺の先のノードより前に来るように並べる。DAG であることと topological sort 出来ることは同値。閉路検出機能は作っていません。

* `topological_sort(edges)`: topological sort された頂点の配列を返す。入力された `edges` が DAG でないなら空の配列を返す。 $O(n+m)$ (ただし、 $n = (頂点数)、m = (辺数)$)

## Refs
* [トポロジカルソートのアルゴリズム（閉路のない有向グラフDAGのソート）](https://algo-logic.info/topological-sort/), 634kami
