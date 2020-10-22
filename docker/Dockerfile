# Copyright (c) 2020 Johannes Stoelp
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
      gdb-multiarch                \
      qemu-user                    \
 && rm -rf /var/lib/apt/lists/*    \
 && apt-get clean                  \
 # Remove expensive qemu emulators which are currently not used.
 && rm -f $(find /usr/bin -name 'qemu-*' | grep -v 'qemu-aarch64$')

WORKDIR /develop
