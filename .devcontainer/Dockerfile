# Refs:
#   https://github.com/microsoft/vscode-remote-try-cpp
#   https://qiita.com/Yuki_Oshima/items/d3b52c553387685460b0
ARG VARIANT=ubuntu-20.04
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt update \

    # By default, it goes to an overseas server to get the repository data.
    # This will slow down the communication speed, so switch to a Japanese server.
    && sed -i -e "s%http://.*.ubuntu.com%http://ftp.jaist.ac.jp/pub/Linux%g" /etc/apt/sources.list \

    # Install `software-properties-common`,
    #   which includes `add-apt-repository`.
    && apt update \
    && apt -y upgrade \
    && apt install -y software-properties-common \
    # Add the universe repository.
    #   (If not, pip cannot be installed.)
    && add-apt-repository universe \

    # Install.
    && apt update \
    && apt install -y build-essential gdb python3 shellcheck time bc xdg-utils flake8 pkg-config ruby-bundler libssl-dev \

    # Install tools that require `pip`.
    && apt update \
    && apt install -y python3-pip \
    && pip install autopep8 pylint numpy scikit-learn \
    && pip3 install selenium online-judge-tools online-judge-verify-helper \
    && python3 -m pip install --upgrade requests \

    # [Optional] Set up C#
    # && apt update \
    # && apt install -y dotnet-sdk-3.1 \

    # [Optional] Set up Go
    # -y オプションはないかも
    # && add-apt-repository -y ppa:longsleep/golang-backports \
    # && apt install -y golang \
    # && go mod init compro \
    # && go mod download github.com/stretchr/testify \

    # Update and upgrade.
    && apt update \
    && apt -y upgrade
