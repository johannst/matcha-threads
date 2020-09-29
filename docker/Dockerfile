# Copyright (c) 2020 Johannes Stoelp
FROM ubuntu:20.04

RUN apt update                     \
 && DEBIAN_FRONTEND=noninteractive \
    apt install -y                 \
      git                          \
      make                         \
      gcc                          \
      g++                          \
      gcc-aarch64-linux-gnu        \
      g++-aarch64-linux-gnu        \
      gdb-multiarch                \
      qemu-user                    \
      neovim                       \
 && rm -rf /var/lib/apt/lists/*    \
 && apt-get clean

WORKDIR /develop
