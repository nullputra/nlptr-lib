---
title: Traveling Salesman Problem (巡回セールスマン問題)
documentation_of: //lib/cpp/dp/traveling-salesman-problem.hpp
---
## Brief
* `traveling_salesman_problem(dists)`: 隣接行列 `dists` から巡回セールスマン問題を解く。すなわち、重み付き有向グラフ `dists` において、ある始点から全頂点をちょうど 1 回ずつ訪問する最小コストを返す。 $O(n 2^n)$

## Refs
* [ビット演算 (bit 演算) の使い方を総特集！ 〜 マスクビットから bit DP まで 〜](https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#11-bit-dp), drken
