#!/bin/bash

# [Optional]
# 1. Configure ssh related settings for connecting to github.
# 1-1. Create ~/.ssh/config, ~/.ssh/ed25519, and ~/.ssh/ed25519.pub
# Refs:
#   https://docs.github.com/ja/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
#   https://qiita.com/shizuma/items/2b2f873a0034839e47ce
ssh-keygen -t ed25519 -N "" -C "nlptr-lib" -f ~/.ssh/ed25519
echo -e "Host github github.com\\n  HostName github.com\\n  IdentityFile ~/.ssh/ed25519\\n  User git" > ~/.ssh/config
eval "$(ssh-agent -s)"
# chmod 600 ~/.ssh/ed25519
# chmod 644 ~/.ssh/ed25519.pub

ssh-add ~/.ssh/ed25519
column_lim=$(tput cols)
[[ $column_lim -gt 120 ]] && column_lim=120
seq -s "-" 0 "$column_lim" | tr -d "0-9"
echo "On https://github.com/settings/keys, click on the \"New SSH keys\" button and paste the public key listed below."
echo "(You can check if the connection settings are correct by using the following command: \"ssh -T github.com.nl\")"
C_BOLD="\033[1;39;49m"
C_RESET="\033[m"
echo -en "${C_BOLD}"
cat ~/.ssh/ed25519.pub
echo -en "${C_RESET}"
seq -s "-" 0 "$column_lim" | tr -d "0-9"

# 1-2. Add settings to ~./gitconfig
# Ref: https://qiita.com/y-tsutsu/items/2ba96b16b220fb5913be
git init
git config --local user.name "nullputra"
git config --local user.email "stdnlptr@gmail.com"
git config --local url.ssh://git@github.com.nl/.insteadOf https://github.com/
git config --global core.editor "code --wait"
git config --global merge.tool 'code --wait "$MERGED"'
git config --global push.default simple

cat << EOF
## 1-2. Execute the following command to create the repository.
##      You may need the following command: "git pull origin master"
# git remote add origin git@github.com.nl:nullputra/nlptr-lib.git
# git add --all && git commit -m "First commit" && git push --all
## Partial push
# git push origin master:master
EOF

# chmod 600 ~/.ssh/github_id_rsa

# [Optional]
# 2. chmod 700, 7 means rwx
# Ref: https://qiita.com/ntkgcj/items/6450e25c5564ccaa1b95
chmod 700 ./cptest.sh ./generate.py ./judge.py

# [Optional]
# 3. Install rust
cat << EOF
# 3-1. Install rust.
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env
rustup install nightly
# rustup install stable
# rustup update nightly
# rustup default nightly
rustup update
rustup component add clippy rls rust-analysis rust-src rust-docs rustfmt

# 3-2. Set config for cargo.
echo -e "[net]\ngit-fetch-with-cli = true" >> ~/.cargo/config

# 3-3. Install rustfmt.
cargo install rustfmt

# 3-5. Automatic generation of a set of files required for build and execution.
cargo new <PROJECT_NAME>

# 4-1. Install CMake
# Ref: https://cmake.org/install/
curl -OL https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1-SHA-256.txt
curl -OL https://github.com/Kitware/CMake/releases/download/v3.20.1/cmake-3.20.1.tar.gz
sha256sum -c --ignore-missing cmake-3.20.1-SHA-256.txt
EOF
