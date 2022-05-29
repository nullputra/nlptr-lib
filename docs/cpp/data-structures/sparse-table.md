---
title: Sparse Table
documentation_of: //lib/cpp/data-structures/sparse-table.hpp
---
## Brief
更新がない場合に使える。区間の最大値・最小値を求める。演算は min、max の他に gcd、lcm も使える。なお、全てのクエリについて 「`l`、`r` の少なくとも一方が区間の端」のときは, 左右からの累積 min、max、gcd か lcm の方が高速 ($\Theta(n)$)。

* constructor `SparseTable(v, f)`: 配列 `v`, 演算関数 $f$ を用いて初期化。なお $v[i][j] := (区間 [j,j+2^i) に演算 f を適用した結果)$ です。 $\Theta(n \log n)$
* `get(l, r)`: 区間 $[l, r)$ に対し演算 $f$ を適用した結果を返す。機構としては $f[l,r) = f{ f[l,l+i), f[r-i,r) }$ です。 $\Theta(1)$
* `print()`: デバッグ用。 $\Theta(n \log n)$

## Refs
* [https://ei1333.github.io/library/structure/others/sparse-table.cpp](https://ei1333.github.io/library/structure/others/sparse-table.cpp), ei1333
* [Sparse Table いかたこのたこつぼ](https://ikatakos.com/pot/programming_algorithm/data_structure/sparse_table), ikatakos
