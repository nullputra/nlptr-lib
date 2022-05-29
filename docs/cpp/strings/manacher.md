---
title: Manacher
documentation_of: //lib/cpp/strings/manacher.hpp
---
## Brief
最長回文。snuke さんによれば「このままでは奇数長の回文しか検出できませんが、「a\$b\$a\$a\$b」みたいにダミー文字を間に挟むと偶数長のものも検出できるようにできます。」とのことです。  
実装に関しては、`reused_len` $:= (再利用する文字列長) + 1$ であり、`r[i-reused_len,i-1] -> r[i+1,i+reused_len]` のように再利用します。

* `manacher(s)`: `r[i]` $:= (s[i] を中心とする最長の回文の半径)$ 。半径というのは、$\frac{(全長)+1}{2}$ のことです。 $\Theta(n)$ (ただし $n := \left|s\right|$ )

## Refs
* [文字列の頭良い感じの線形アルゴリズムたち２ - Manacher](https://snuke.hatenablog.com/entry/2014/12/02/235837), snuke
