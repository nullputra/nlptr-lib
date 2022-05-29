# 🦀 Rust の環境構築

## 1. WSL を入れます

- 参考: [lib/set-up-wsl](https://nullputra.github.io/nlptr-lib/set-up-wsl.html)

## 2. `rustup` などのツールのインストール

あなたの OS が UNIX なら以下のコマンドを実行して `rustup` をインストールしてください。その他の OS なら、[Rust をインストール](https://www.rust-lang.org/ja/tools/install) や [Windows で Rust 用の開発環境を設定する](https://docs.microsoft.com/ja-jp/windows/dev-environment/rust/setup) を参照してください。

#### ターミナル

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
# 変更の反映
source $HOME/.cargo/env
# 安定版をインストール
rustup install nightly
# 最新版にアップデート
rustup update
# rustup の便利なコンポーネントをインストール
rustup component add clippy rls rust-analysis rust-src rust-docs rustfmt

# cargo 用の設定
echo -e "[net]\ngit-fetch-with-cli = true" > ~/.cargo/config
# cargo を用いて rustfmt をインストール
cargo install rustfmt
```

## 3. ビルドや実行に必要なファイル群の自動生成

以下のコードを実行すると、カレントディレクトリ直下に `<PROJECT_NAME>` というディレクトリが作られ、`./Cargo.toml` などのビルドや実行に必要なファイル群が生成されます。

#### ターミナル

```sh
cargo new <PROJECT_NAME>
cd <PROJECT_NAME>
```

#### `./Cargo.toml` に追記

競プロで使いそうなものを `./Cargo.toml` の \[dependencies\] に追記します。

```ini
# Ref: https://github.com/rust-lang-ja/atcoder-rust-base/blob/ja-all-enabled/Cargo.toml
[dependencies]
ascii = "1.0.0"
bitset-fixed = "0.1.0"
itertools = "0.10.3"
num = "0.4.0"
num-traits = "0.2.11"
modtype = "0.7.0"
ordered-float = "2.8.0"
proconio = { version = "0.3.6", features = ["derive"] }
rand = { version = "0.7.3", features = ["small_rng"] }
rand_pcg = "0.2.1"
regex = "1.5.4"
```

また、`cargo` で rs ファイルを扱う際、 `./Cargo.toml` に以下のように `[[bin]]` を追記しなければなりません。作った rs ファイルそれぞれに対し、以下を追記します。なお、`<BINARY_NAME>` は何でもいいですが、管理の都合上 `<FILE_NAME>` と同じにしておくのがお薦めです。

#### ./Cargo.toml に追記

```ini
[[bin]]
name = "<BINARY_NAME>"
path = "src/<FILE_NAME>.rs"
```

## 4. ビルドと実行

以下のコマンドで全てのファイルをビルドできます。ビルドするとバイナリファイルが `./target/debug/<FILE_NAME>` に作られます。

#### ターミナル

```sh
cargo build --release --bin <BINARY_NAME>
```

バイナリファイルを実行するには以下のいずれかのようにします。

#### ターミナル

```sh
# A. バイナリファイルを実行します。入力を手打ちする必要があります。
./target/debug/<BINARY_NAME>

# B. input.txt を入力として、バイナリファイルを実行します。
./target/debug/<BINARY_NAME> < ./input.txt
```

`cargo run --bin <BINARY_NAME>` なら、ビルドと実行を一括で行えます。

#### ターミナル

```sh
# ビルドと実行を別々に行う
# cargo build
# ./target/debug/<BINARY_NAME> < ./input.txt

# 上の二行を一括で行えるコマンド
cargo run
```

---

以下、VSCode で rust を使うときのお薦め設定です。

## 5. 静的解析ツール clippy を設定

[How to use Clippy in VS Code with rust-analyzer?](https://users.rust-lang.org/t/how-to-use-clippy-in-vs-code-with-rust-analyzer/41881/2) に従って設定します。

## 6. おすすめ VSCode 拡張機能

- `bungcip.better-toml`  
  toml のシンタックスハイライト。
- `serayuzgur.crates`  
  公式によると「Helps Rust developers managing dependencies with Cargo.toml.」とのことです。
- `matklad.rust-analyzer`  
  `rust-lang.rust` と同様の機能を持つ拡張機能。

## 7. ソースコードにライブラリを bundle する

自動でライブラリファイルからバンドルしてくれるコードを書きました: [lib/rust/expander.py](https://github.com/nullputra/nlptr-lib/blob/master/lib/rust/expander.py)  
使い方を以下の通りです。

#### 用意するもの (1): src/main.cs

```rs
// https://atcoder.jp/contests/abc120/tasks/abc120_d
use proconio::input;
use proconio::marker::*;
include!("../lib/rust/data_structures/union_find.rs");
fn main() {
    input! {
        (n, m): (usize, usize),
        ab: [(Usize1, Usize1); m],
    }
    let mut uf = UnionFind::new(n);
    let f = |x| x * (x - 1) / 2;
    let mut cur = f(n);
    let mut ans = vec![cur; m + 1];
    for (i, &(a, b)) in ab.iter().rev().enumerate() {
        if uf.same(a, b) {
            ans[i + 1] = cur;
            continue;
        }
        let x = uf.size(a);
        let y = uf.size(b);
        cur -= f(x + y) - f(x) - f(y);
        ans[i + 1] = cur;
        uf.unite(a, b);
    }
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    use std::io::Write;
    for i in (0..m).rev() {
        writeln!(out, "{}", ans[i]).unwrap();
    }
}
```

#### 用意するもの (2): lib/rust/data_structures/union_find.rs

```rs
// Union Find
//
// # Refs
// - https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/dsu.rs, rust-lang-ja Developers
struct UnionFind {
    n: usize,
    par: Vec<i32>,
}
#[allow(dead_code)]
impl UnionFind {
    fn new(n: usize) -> Self {
        UnionFind {
            n,
            par: vec![-1; n],
        }
    }
    fn unite(&mut self, mut x: usize, mut y: usize) -> bool {
        assert!(x < self.n && y < self.n);
        x = self.find(x);
        y = self.find(y);
        if x == y {
            return false;
        }
        if self.par[x] > self.par[y] {
            std::mem::swap(&mut x, &mut y);
        }
        self.par[x] += self.par[y];
        self.par[y] = x as i32;
        true
    }
    fn find(&mut self, x: usize) -> usize {
        assert!(x < self.n);
        if self.par[x] < 0 {
            x
        } else {
            self.par[x] = self.find(self.par[x] as usize) as i32;
            self.par[x] as usize
        }
    }
    fn same(&mut self, x: usize, y: usize) -> bool {
        assert!(x < self.n && y < self.n);
        self.find(x) == self.find(y)
    }
    fn groups(&mut self) -> Vec<Vec<usize>> {
        let mut _find = vec![0; self.n];
        let mut _size = vec![0; self.n];
        for i in 0..self.n {
            _find[i] = self.find(i);
            _size[_find[i]] += 1;
        }
        let mut res = vec![vec![]; self.n];
        for i in 0..self.n {
            res[i].reserve(_size[i]);
        }
        for i in 0..self.n {
            res[_find[i]].push(i);
        }
        res.into_iter()
            .filter(|v| !v.is_empty())
            .collect::<Vec<Vec<usize>>>()
    }
    fn size(&mut self, x: usize) -> usize {
        assert!(x < self.n);
        let x = self.find(x);
        -self.par[x] as usize
    }
}
```

以上を用意して、ターミナルで下のコマンドを実行します。

#### ターミナル

```sh
lib/rust/expander.py src/main.cs > src/main_bundled.cs
```

#### 生成されるもの: src/main_bundled.cs

```rs
use proconio::input;
use proconio::marker::*;
struct UnionFind {
    n: usize,
    par: Vec<i32>,
}
#[allow(dead_code)]
impl UnionFind {
    fn new(n: usize) -> Self {
        UnionFind {
            n,
            par: vec![-1; n],
        }
    }
    fn unite(&mut self, mut x: usize, mut y: usize) -> bool {
        assert!(x < self.n && y < self.n);
        x = self.find(x);
        y = self.find(y);
        if x == y {
            return false;
        }
        if self.par[x] > self.par[y] {
            std::mem::swap(&mut x, &mut y);
        }
        self.par[x] += self.par[y];
        self.par[y] = x as i32;
        true
    }
    fn find(&mut self, x: usize) -> usize {
        assert!(x < self.n);
        if self.par[x] < 0 {
            x
        } else {
            self.par[x] = self.find(self.par[x] as usize) as i32;
            self.par[x] as usize
        }
    }
    fn same(&mut self, x: usize, y: usize) -> bool {
        assert!(x < self.n && y < self.n);
        self.find(x) == self.find(y)
    }
    fn groups(&mut self) -> Vec<Vec<usize>> {
        let mut _find = vec![0; self.n];
        let mut _size = vec![0; self.n];
        for i in 0..self.n {
            _find[i] = self.find(i);
            _size[_find[i]] += 1;
        }
        let mut res = vec![vec![]; self.n];
        for i in 0..self.n {
            res[i].reserve(_size[i]);
        }
        for i in 0..self.n {
            res[_find[i]].push(i);
        }
        res.into_iter()
            .filter(|v| !v.is_empty())
            .collect::<Vec<Vec<usize>>>()
    }
    fn size(&mut self, x: usize) -> usize {
        assert!(x < self.n);
        let x = self.find(x);
        -self.par[x] as usize
    }
}
fn main() {
    input! {
        (n, m): (usize, usize),
        ab: [(Usize1, Usize1); m],
    }
    let mut uf = UnionFind::new(n);
    let f = |x| x * (x - 1) / 2;
    let mut cur = f(n);
    let mut ans = vec![cur; m + 1];
    for (i, &(a, b)) in ab.iter().rev().enumerate() {
        if uf.same(a, b) {
            ans[i + 1] = cur;
            continue;
        }
        let x = uf.size(a);
        let y = uf.size(b);
        cur -= f(x + y) - f(x) - f(y);
        ans[i + 1] = cur;
        uf.unite(a, b);
    }
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    use std::io::Write;
    for i in (0..m).rev() {
        writeln!(out, "{}", ans[i]).unwrap();
    }
}
```

## 8. 参考文献

- [RustCoder - 環境構築](https://zenn.dev/toga/books/rust-atcoder/viewer/02-environment-setup)
- [Rust 入門日記 - 標準入力](https://zenn.dev/link/comments/3199fbe14f9b23)
