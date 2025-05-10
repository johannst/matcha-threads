# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020, Johannes Stoelp <dev@memzero.de>

FROM ubuntu:latest

RUN apt update                     \
 && DEBIAN_FRONTEND=noninteractive \
    apt install                    \
      --yes                        \
      --no-install-recommends      \
      make                         \
      gcc                          \
      g++                          \
      gcc-aarch64-linux-gnu        \
      g++-aarch64-linux-gnu        \
      gcc-arm-linux-gnueabi        \
      g++-arm-linux-gnueabi        \
      gcc-riscv64-linux-gnu        \
      g++-riscv64-linux-gnu        \
      gdb-multiarch                \
      qemu-user                    \
 && rm -rf /var/lib/apt/lists/*    \
 && apt-get clean                  \
 # Remove expensive qemu emulators which are currently not used.
 && rm -f $(find /usr/bin -name 'qemu-*' | grep -v 'qemu-aarch64$\|qemu-arm$\|qemu-riscv64$')

WORKDIR /develop
