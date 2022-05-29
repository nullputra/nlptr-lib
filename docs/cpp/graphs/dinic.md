---
title: Dinic (最大流)
documentation_of: //lib/cpp/graphs/dinic.hpp
---
## Brief
Dinic 法。最大流問題を解く。以下、 $m = (辺数)$ とする。

* `dinic(n)`: 頂点数 `n` を指定。 $\Theta(1)$
* `add_edge(from, to, cap)`: `from` から `to` へ最大容量 `cap` の辺を追加。 $\Theta(1)$
* `get_edge(i)`: i 番目に追加した辺を返す。 $\Theta(1)$
* `get_edges()`: 全ての辺の配列を返す。 $\Theta(m)$
* `for_each_path(f)`: それぞれの path に対し関数 f を作用する。 $\Theta(m)$ (関数 `f` が $\Theta(1)$ のとき)
* `change_edge(new_cap, new_flow)`: i 番目に追加した辺の容量, 流量を `new_cap`, `new_flow` に変更する。 $\Theta(1)$
* `flow(s, t, f_lim)`: 頂点 `s` から `t` へ流量が `f_lim` 以下の範囲でできる限り流し, 流した量を返す。 計算量は $O(n^2 m)$ だが, worst case となることは殆どない。
* `min_cut(s)`: 頂点 `s` から `i` への残余グラフで到達可能かどうかの配列を返す。 $O(n+m)$

## Refs
* [https://github.com/atcoder/ac-library/blob/master/atcoder/maxflow.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/maxflow.hpp), yosupo
