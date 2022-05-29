---
title: Z Algorithm (最長共通接頭辞)
documentation_of: //lib/cpp/strings/z-algorithm.hpp
---
## Brief
* `z_algorithm(s, x = 0)`: 文字列 `s[x:]` に対して求めた $z$ を返す。実装に関しては、`reused_len` $:= (再利用する文字列長) + 1$ であり、 `z[1:reused_len] -> z[i+1:i+reused_len]` のように再利用する。
$\Theta(n)$ ($n = \left|s\right|$ とした)  
  e.g. `s = "ababa" -> [5, 0, 3, 0, 1]`
* `z_search(s, ptn)`: `z_idx` を返す。 $\Theta(n)$  
  e.g. `s = "ababa", ptn = "aba" -> [0, 2]`

## Refs
* [文字列の頭良い感じの線形アルゴリズムたち３ - Z algorithm](https://snuke.hatenablog.com/entry/2014/12/03/214243), snuke
