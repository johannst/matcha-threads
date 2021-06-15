#!/bin/bash
# Copyright (c) 2020 Johannes Stoelp

image=${1:-matcha-box}

script_dir=$(dirname $(readlink -f $0))

if ! docker build -t $image $script_dir ; then
    echo "ERR: Failed to build docker image!"
    exit 1
fi

exit 0
