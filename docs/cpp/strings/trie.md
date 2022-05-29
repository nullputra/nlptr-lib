---
title: Trie (トライ木)
documentation_of: //lib/cpp/strings/trie.hpp
---
## Brief
* constructor `Trie<W>()`: `s_w` の型を `W` で初期化. `s_w` を使わないなら void を入れておく。 $\Theta(1)$
* `insert(s, s_w = -1)`: 文字列 `s` を挿入。 $\Theta(\left|s\right|)$
* `find(t, f, s_l = 0, t_l = 0)`: `t_r = t_l, t_l+1, ..., n` に対し、「いずれかの `s[s_l:]` の prefix」と「`t[t_l:t_r+1]`」とが一致するごとに関数 `f` が呼び出される。 $O( \left|t\right| )$
* `print(cur = 0)`: デバッグ用。`cur` は $0$ のままで実行してください。 $O(\sum \left|s\right| )$

## Refs
* [トライ木(Trie木) の解説と実装【接頭辞(prefix) を利用したデータ構造】](https://algo-logic.info/trie-tree/)
* [トライ木(Trie)｜Luzhiled's memo](https://ei1333.github.io/luzhiled/snippets/structure/trie.html)
