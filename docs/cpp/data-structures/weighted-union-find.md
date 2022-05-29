---
title: Weighted Union Find
documentation_of: //lib/cpp/data-structures/weighted-union-find.hpp
---
## Brief
集合同士の重みの差分の情報を持つデータ構造。集合同士の合併 (`merge`)、ある要素がどの集合に属しているか (`find`)、集合同士の重さの差の取得 (`diff`) をならし $O(\alpha(n))$ 時間で処理できる ($\alpha$ はアッカーマンの逆関数)。差分制約系の問題 ([牛ゲー](https://tjkendev.github.io/procon-library/python/graph/difference-constraints-ushi.html)など) に用いる。

* constructor `WeightedUnionFind(n, id)`: 集合の要素数の最大を `n`、加算と減算の定義された型 (アーベル群という) `T` の単位元 (大抵は `0`) を `id` で初期化。
* `merge(x, y, w)`: 要素 `x`、`y` に対し `wts[y] - wts[x] == w` が成り立つように合併する。`merge` が必要だったかを返す。 $O(n)$
* `find(x)`: 要素 `x` が属する集合の根 (代表要素) を返す。ならし $O(\alpha(n))$
* `weight(x)`: 要素 `x` が属する集合の重さの総和 `wts[x]` を返す。ならし $O(\alpha(n))$
* `diff(x, y)`: 要素 `x`、`y` が属する集合の重さの差 `wts[y] - wts[x]` を返す。符合付きなので注意。ならし $O(\alpha(n))$
* `same(x, y)`: 要素 `x`、`y` が同じ集合に属するかを返す。ならし $O(\alpha(n))$
* `size(x)`: 要素 `x` が属する集合の要素の数を返す。ならし $O(\alpha(n))$

## Refs
* [https://ei1333.github.io/library/structure/union-find/weighted-union-find.cpp](https://ei1333.github.io/library/structure/union-find/weighted-union-find.cpp), ei1333
* [重み付き Union-Find 木とそれが使える問題のまとめ、および、牛ゲーについて](https://qiita.com/drken/items/cce6fc5c579051e64fab), drken
