---
title: Prim
documentation_of: //lib/cpp/graphs/prim.hpp
---
## Brief
Prim 法ですが隣接リストではなく隣接行列を受け取ります。無向グラフに対し、全域を包囲できる木の最小コストを取得する。この時に作られる木を最小全域木という。

* constructor `Prim(adja)`: 頂点間に結ばれるコストを表す隣接行列 `adja` を受け取り、最小全域木を構成する辺のコストの総和を返す。 $\Theta(n^2)$ (ただし $n = (頂点数)$)

### Note
MST 構築は作っていません。 (Kruskal を使えばいいため)  

## Refs
* [プリム法による最小全域木を求めるアルゴリズム](https://algo-logic.info/prim-mst/), 634kami
