---
title: Morris Pratt (MP 法)
documentation_of: //lib/cpp/strings/morris-pratt.hpp
---
## Brief
* `morris_pratt(s, is_knuth)`: $b[i] := (s[0,i) の最長 border)$ (ただし $b[0] = -1$ )。border というのは prefix かつ suffix なる文字列のことです。 $b[n]$ だけ求まればよい場合は `is_knuth` を `true` にしてよく、定数倍高速です。 $\Theta(n)$ (ただし $n := |s|$ )  
  e.g. `is_knuth == true`: `s = "aabaabaaa" -> [-1, 0, 1, 0, 1, 2, 3, 4, 5, 2]`  
       `is_knuth == false`: `s = "aabaabaaa" -> [-1, -1, 1, -1, -1, 1, -1, -1, 5, 2]`

## Refs
* [文字列の頭良い感じの線形アルゴリズムたち - KMP](https://snuke.hatenablog.com/entry/2014/12/01/235807), snuke
