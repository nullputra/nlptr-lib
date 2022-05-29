# 🌽 競プロ環境構築 WSL (+ VSCode) for Windows

もちろん Windows 上でもプログラミングはできるけど、WSL を使うと Windows 上で Ubuntu のコマンドを使える。プログラマ向けのソフトは Ubuntu 上の方が扱いやすいので WSL を導入すべき。

## 1. WSL2 を使えるように環境設定 (コマンドプロンプトにて)

### 1-1. Linux 用 Windows サブシステムの有効化および仮想マシンプラットフォームの有効化

コンパネ＞アンインストール＞左列の「Windows の機能の有効化または無効化」で「Linux 用 Windows サブシステム」および「仮想マシンプラットフォーム」にチェックを入れる。終わったら PC を再起動して有効化する。

### 1-2. WSL のバージョンのデフォルトを version 2 に設定 (導入確認: `wsl -l -v`)

WSL は Windows Subsystem for Linux (Linux 用 Windows サブシステム) の略。

```
wsl --set-default-version 2
```

## 2. Ubuntu 20.04 LTS 導入

Microsoft Store から「Ubuntu 20.04 LTS」をインストール。そして、Ubuntu20.04 を起動すると、ユーザー名とパスワードの設定を求められるので好きなのを入れる。注意として、ユーザー名とパスワードを入力する際に画面に何も表示されないが、しっかり入力されている。

<img src="https://i.imgur.com/ZjEXdwi.png" title="Ubuntu" width="500">

## 3. Ubuntu 調整

デフォルトでは海外サーバーにリポジトリのデータを取りに行ってしまう。これだと通信速度が遅いので、日本のサーバーに切り替え(1 行目)。更新もしとく(2、3 行目)。  
なお、sudo は「スードゥー」と発音するらしい。

#### ターミナル

```sh
sudo sed -i -e "s%http://.*.ubuntu.com%http://ftp.jaist.ac.jp/pub/Linux%g" /etc/apt/sources.list
sudo apt update
sudo apt upgrade
```

## 4. 実行環境いろいろ (自分の使う言語のやつだけインストールしてね)

### 4-1. (for C++) C++ コンパイラの `g++`、C++ デバッガ `gdb` 導入

(なお、以下のような途中まで同じコマンドは`sudo apt install build-essentail gdb`と、一行で実行することも可能)

#### ターミナル

```
sudo apt install build-essential
sudo apt install gdb
```

### 4-2. (for Python) Python コンパイラの `python3`、コード整形ツール `autopep8` 導入、競プロ用自動化ツール `online-judge-tools`

下記の Python3 インストールが終わると、`python3` と打つことで Python 対話モードになる。さらに 2+3 と打つと、5 が出力されるはず。`[ctrl + z]` で対話モードを終了。  
また、カレントディレクトリ上の foo.py を実行するには `python3 foo.py` とする。

#### ターミナル

```sh
sudo apt install python3

# pip / pip3 のインストールには universe レポジトリを検索対象に含める必要がある
sudo apt update
apt install -y software-properties-common
add-apt-repository universe

# pip / pip3 のインストール
sudo apt update
apt install -y python3-pip

# numpy は python 使うなら必須の数値計算モジュール
pip3 install numpy
```

## 5. 競プロ用自動化コマンド `oj` 導入 (導入確認: `oj --version`)

#### ターミナル

```sh
# pip のインストールが必要なので 4.B. でしなかった人はしてください
# sudo apt update
# apt install -y software-properties-common
# add-apt-repository universe
# sudo apt update
# apt install -y python3-pip
sudo pip3 install online-judge-tools
```

## 6. VSCode に便利な拡張機能を入れる

WSL を使うなら統合開発環境は [VSCode](https://code.visualstudio.com/download) 一択だと思います。  
サイドバー (左端のバー) の正方形 4 つのタブを開いてください。ここから拡張機能を入れられます。

### おすすめの VSCode 上で LOCAL に入れる拡張機能

- Japanese Language Pack

  日本語化。

- Material Icon Theme

- Remote - Containers

### おすすめの VSCode 上で WSL:Ubuntu-20.04 に入れる拡張機能

- GitHub Copilot

- Highlight Trailing White Spaces

- Prettier

## -1. おわり

以上！お疲れさま！
