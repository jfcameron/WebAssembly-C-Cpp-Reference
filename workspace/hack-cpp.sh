#!/usr/bin/env bash

emcc \
    ../src/main.cpp \
    -s WASM=1 \
    -o ../build/main.html
