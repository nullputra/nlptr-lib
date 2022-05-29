---
title: Bellman Ford
documentation_of: //lib/cpp/graphs/bellman-ford.hpp
---
## Brief
Bellman Ford 法。有向グラフに対し、ある始点から他の頂点への最短距離の配列を求める。負閉路も検出できる。

* constructor `BellmanFord(n, m)`: 頂点数 `n`、辺数 `m` で初期化。`m` は vector の reserve に使うだけなので $0$ でもよい。$\Theta(1)$
* `add_edge(from, to, dist)`: 頂点 `from` から `to` に距離 `dist` の有向辺を張る。 $\Theta(1)$
* `dists(s = -1, g = -1)`: 他の頂点への最短距離の配列を返す。$O(nm)$
  - 1. `s == -1, g == -1` のとき: ただし、始点は任意とし、負閉路があれば代わりに空の配列を返す。
  - 2. `s != -1, g == -1` のとき: ただし、始点 `s` から到達可能である負閉路があれば、代わりに空の配列を返す。
  - 3. `s != -1, g != -1` のとき: ただし、始点 `s` から終点 `g` に至るまでに負閉路があれば、代わりに空の配列を返す。([ABC061 D](https://atcoder.jp/contests/abc061/tasks/abc061_d) に特化しています)  
  (以下参考)
  - 1. 2. `g == -1` のとき: 最短経路の長さは最大 $n-1$ なので $n$ 重のループを回している。
  - 3. `s != -1, g != -1` のとき: 負閉路の長さは最大 $n$、最短経路の長さは最大 $n-1$ なので、計 $2 n-1$ 重のループを回す必要がある。(Refs に載せた editorial.pdf も参照してください)
* `print()`: デバッグ用。これまでに入力した `edges` を cout する。 $\Theta(m)$

## Refs
* [[ABC061 D](https://atcoder.jp/contests/abc061/tasks/abc061_d) editorial.pdf](https://img.atcoder.jp/abc061/editorial.pdf#page=3)
* [ベルマンフォード法について ～負閉路の扱い～](https://mhrb-minase.hatenablog.com/entry/2019/08/20/003915), mhrb
* [ベルマンフォード法による単一始点最短経路を求めるアルゴリズム](https://algo-logic.info/bellman-ford/), 634kami
