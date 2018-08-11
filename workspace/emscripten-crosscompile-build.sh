#!/usr/bin/env bash

mkdir -p src/resource/ && cp ../resource/* "$_"

cmake \
  -G "Unix Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake \
  \
  .. && make
