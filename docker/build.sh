#!/bin/bash
# Copyright (c) 2020 Johannes Stoelp

if ! docker build -t matcha-box . ; then
    echo "ERR: Failed to build docker image!"
    exit 1
fi

exit 0
