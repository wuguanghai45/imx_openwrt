FROM ubuntu:24.04

USER root

ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Shanghai \
    LANG=C.UTF-8

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential clang flex bison g++ gawk \
        gcc-multilib g++-multilib gettext git libncurses5-dev libssl-dev \
        python3-setuptools rsync swig unzip zlib1g-dev file wget \
        bash-completion \
        ca-certificates \
        curl \
        less \
        lua5.1 \
        nano \
        libgnutls28-dev \
        procps \
        shellcheck \
        vim && \
    rm -rf /var/lib/apt/lists/*

RUN ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone

WORKDIR /root/workspace
