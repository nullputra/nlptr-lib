# 🍇 C++ の環境構築

## 1. WSL, build-essential を入れます
- 参考: [lib/set-up-wsl](https://nullputra.github.io/nlptr-lib/set-up-wsl.html)


## 2. `oj-bundle` のインストール
ライブラリ展開コマンド `oj-bundle` は、`online-judge-verify-helper` (別名 [verification-helper](https://github.com/online-judge-tools/verification-helper)) の中に入っています。  

まず `python3`、`pip3` をインストールしてから、`online-judge-verify-helper` をインストールします。  
```sh
sudo apt install python3

# pip / pip3 のインストールには universe レポジトリを検索対象に含める必要がある
apt -y install software-properties-common
add-apt-repository universe

# pip / pip3 のインストール
apt install python3-pip

# online-judge-verify-helper のインストール
pip3 install online-judge-verify-helper
```


## 3. 実際にバンドルを実行する方法
`oj-bundle` でバンドルされる様子は以下のようになります。


#### 用意するもの (1): src/main.cpp
```cpp
#include <bits/stdc++.h>
using namespace std;

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_12_A"
#include "graphs/prim.hpp"
// 環境設定によっては、以下のようにしないとエラーが出る
// #include "../lib/cpp/graphs/prim.hpp"

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adja(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adja[i][j];
        }
    }
    Prim pr(adja);
    cout << pr.cost_tot << '\n';
}
```

#### 用意するもの (2): lib/cpp/graphs/prim.hpp
```cpp
template <class T>
struct Prim {
    T cost_tot = 0;
    static constexpr T TINF = numeric_limits<T>::max();
    Prim(vector<vector<T>> &adja) {
        int n = adja.size();
        vector<T> min_cost(n, TINF);
        min_cost[0] = 0;
        vector<bool> vis(n);
        while (true) {
            int from = -1;
            for (int u = 0; u < n; u++) {
                if (!vis[u] && (from == -1 || min_cost[u] < min_cost[from])) from = u;
            }
            if (from == -1) break;
            vis[from] = true;
            cost_tot += min_cost[from];
            for (int to = 0; to < n; to++) {
                if (adja[from][to] != -1) min_cost[to] = min(min_cost[to], adja[from][to]);
            }
        }
    }
};
```

以上を用意して、ターミナルで下のコマンドを実行します。  
#### ターミナル
```sh
oj-bundle -I./lib/cpp src/main.cpp | sed '/PROBLEM/d' | sed '/line/d' > src/main-bundled.cpp
```

#### 生成されるもの: src/main-bundled.cpp
```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Prim {
    T cost_tot = 0;
    static constexpr T TINF = numeric_limits<T>::max();
    Prim(vector<vector<T>> &adja) {
        int n = adja.size();
        vector<T> min_cost(n, TINF);
        min_cost[0] = 0;
        vector<bool> vis(n);
        while (true) {
            int from = -1;
            for (int u = 0; u < n; u++) {
                if (!vis[u] && (from == -1 || min_cost[u] < min_cost[from])) from = u;
            }
            if (from == -1) break;
            vis[from] = true;
            cost_tot += min_cost[from];
            for (int to = 0; to < n; to++) {
                if (adja[from][to] != -1) min_cost[to] = min(min_cost[to], adja[from][to]);
            }
        }
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adja(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adja[i][j];
        }
    }
    Prim pr(adja);
    cout << pr.cost_tot << '\n';
}
```
