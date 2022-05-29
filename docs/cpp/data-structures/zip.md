---
title: Zip (座圧)
documentation_of: //lib/cpp/data-structures/zip.hpp
---
## Brief
* constructor `Zip(n)`: 配列サイズ `n` で初期化。 $\Theta(n \log n)$
* `operator[]`: 座圧前は値の代入用で、座圧後は値の取得用。 $\Theta(1)$<br>
  e.g. `[8, 100, 33, 33, 33, 12, 6, 1211] -> [1, 4, 3, 3, 3, 2, 0, 5]`

## Refs
* [座標圧縮 (座圧)](https://drken1215.hatenablog.com/entry/2021/08/09/235400), drken
