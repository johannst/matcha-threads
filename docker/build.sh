#!/bin/bash
# Copyright (c) 2020 Johannes Stoelp

image=${1:-match-box}

if ! docker build -t $image . ; then
    echo "ERR: Failed to build docker image!"
    exit 1
fi

exit 0
