---
title: Binary Indexed Tree (BIT)
documentation_of: //lib/cpp/data-structures/binary-indexed-tree.hpp
---
## Brief
以下で `i`、`l`、`r` は全て 1-indexed です。  
0-indexed で実装したい方は [atcoder/dsu](https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp) を見てください。

* constructor `BinaryIndexedTree<T>(n)`: 配列サイズ `n` で初期化。 $\Theta(1)$
* `add(x, l, r = -1)`: 区間 $[l,r)$ 内の $i$ に対し `v[i] += x` をする (区間加算)。ただし $r$ を未指定だと `v[l] += x` をする (一点加算)。一点加算と統合したため、変則的だが引数を `x`、`l`、`r` の順としている。 $O(\log n)$
* `sum(i)`: $\sum_{k=1}^{i} v[k]$ を返す。実装の都合上、閉区間なので注意。 $O(\log n)$
* `range_sum(l, r)`: $\sum_{i=l}^{r-1} v[i]$ を返す。 $O(\log n)$
* `operator[](i)`: $v[i]$ を返す。 $O(\log n)$
* `print()`: デバッグ用。 $O(n \log n)$

## Refs
* [Binary Indexed Tree (BIT) 総まとめ！区間加算や二次元BITまで](https://algo-logic.info/binary-indexed-tree/), 634kami
