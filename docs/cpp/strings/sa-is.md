---
title: SA-IS (Suffix Array)
documentation_of: //lib/cpp/strings/sa-is.hpp
---
## Brief
suffix array を $\Theta(n)$ で構築する (ただし $n := \left|s\right|$ )。

* constructor `SA_IS(s, low_ch = '0', high_ch = 'z')`: 文字列 `s` において ASCII 値の最小を `low_ch`, 最大を `high_ch` で指定。
$\Theta(1)$
* `get_sa()`: `s` の suffix array を返す。 $\Theta(n)$
* `contains(t, is_prefix_match)`: `s` が `t` を含むかどうかを返す。`is_prefix_match` が `true` なら部分一致、`false` なら完全一致。実装は二分探索。 $O(\log n)$
* `print()`: デバッグ用。 $\Theta(n)$

## Refs
* [SA-IS 法のメモ](https://mametter.hatenablog.com/entry/20180130/p1), ku-ma-me
* [https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp](https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp), yosupo
