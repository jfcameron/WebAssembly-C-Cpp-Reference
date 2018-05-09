#!/usr/bin/env bash

emcc \
    ../src/main.c \
    -s WASM=1 \
    -o ../build/main.html
