# 🥧 Common Lisp の環境構築

## 1. WSL を入れます
- 参考: [lib/set-up-wsl](https://nullputra.github.io/nlptr-lib/set-up-wsl.html)

## 2. インストール
```sh
sudo apt install -y sbcl
curl -o /tmp/ql.lisp http://beta.quicklisp.org/quicklisp.lisp
sbcl --no-sysinit --no-userinit --load /tmp/ql.lisp \
  --eval '(quicklisp-quickstart:install :path "~/.quicklisp")' \
  --eval '(ql:add-to-init-file)' \
  --quit
```

## 参考文献
- [Getting Started | Common Lisp](https://lisp-lang.org/learn/getting-started/)
