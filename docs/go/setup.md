# 🐹 Go の環境構築

## 1. WSL を入れます
- 参考: [lib/set-up-wsl](https://nullputra.github.io/nlptr-lib/set-up-wsl.html)

## 2. インストール
```sh
sudo add-apt-repository -y ppa:longsleep/golang-backports
sudo apt install -y golang
```

## 3. 参考
### 3-1. Setup
```sh
go mod init compro
```
### 3-2. Install `testify`
```sh
go mod download github.com/stretchr/testify
```
