# ๐น Go ใฎ็ฐๅขๆง็ฏ

## 1. WSL ใๅฅใใพใ
- ๅ่: [lib/set-up-wsl](https://nullputra.github.io/nlptr-lib/set-up-wsl.html)

## 2. ใคใณในใใผใซ
```sh
sudo add-apt-repository -y ppa:longsleep/golang-backports
sudo apt install -y golang
```

## 3. ๅ่
### 3-1. Setup
```sh
go mod init compro
```
### 3-2. Install `testify`
```sh
go mod download github.com/stretchr/testify
```
