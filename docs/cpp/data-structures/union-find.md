---
title: Union Find
documentation_of: //lib/cpp/data-structures/union-find.hpp
---
## Brief
集合を扱うデータ構造 (「Union Find 木」とかかれている文献もあるが、Union Find は木ではない)。集合同士の合併 (`merge`)、ある要素がどの集合に属しているか (`find`) をならし $O(\alpha(n))$ 時間で処理できる ($\alpha$ はアッカーマンの逆関数)。無向グラフ上の dfs の代用として使えることがある。

* constructor `UnionFind(n)`: 集合の要素数の最大を `n` とする。
* `merge(x, y)`: 要素 `x`、`y` の属する集合を合併する。`merge` が必要だったかを返す。 $O(n)$
* `find(x)`: 要素 `x` が属する集合の根 (代表要素) を返す。ならし $O(\alpha(n))$
* `same(x, y)`: 要素 `x`、`y` が同じ集合に属するかを返す。ならし $O(\alpha(n))$
* `size(x)`: 要素 `x` が属する集合の要素数を返す。ならし $O(\alpha(n))$
* `groups()`: 「各集合に含まれる要素の配列」の配列を返す。 $O(n)$

## Refs
* [競プロ覚書：Union-Find まとめ](https://pyteyon.hatenablog.com/entry/2019/03/11/200000), pyteyon
