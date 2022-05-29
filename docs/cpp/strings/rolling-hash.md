---
title: Rolling Hash
documentation_of: //lib/cpp/strings/rolling-hash.hpp
---
## Brief
メルセンヌ素数 $2^{61}-1$ を利用した Rolling Hash。

* `RollingHash(s, randomizes)`: 文字列 `s` で初期化。`randomizes` が `false` のときの計算量は $\Theta(n)$ です。(ただし $n := \left|s\right|$ )
* `slice(l, r)`: `s[l:r]` のハッシュを返す。(ただし, `s[l:r]` $:= (s のうち区間 [l,r) の部分)$ .) $\Theta(1)$
* `get_lcp(a, b)`: `s[a:]` と `s[b:]` の一致文字数を返す。 $O(\log n)$
* `get_lcp(a, rh, b)`: `s[a:]` と `rh.s[b:]` の一致文字数を返す。 $O(\log (min(n,m)))$ (ただし $m := \left|rh.s\right|$ )

## Refs
* [安全で爆速なRollingHashの話](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6), keymoon
