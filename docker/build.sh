#!/bin/bash
# Copyright (c) 2020 Johannes Stoelp

image=${1:-match-box}

script_dir=$(readlink -f $(dirname $0))

if ! docker build -t $image $script_dir ; then
    echo "ERR: Failed to build docker image!"
    exit 1
fi

exit 0
