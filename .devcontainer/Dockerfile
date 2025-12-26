FROM openwrt/sdk:latest

USER root

ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Shanghai \
    LANG=C.UTF-8

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        bash-completion \
        ca-certificates \
        curl \
        git \
        less \
        lua5.1 \
        nano \
        file \
        python3-setuptools \
        gawk \
        libgnutls28-dev \
        procps \
        shellcheck \
        vim \
        wget && \
    rm -rf /var/lib/apt/lists/*

RUN ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone

WORKDIR /root/workspace
