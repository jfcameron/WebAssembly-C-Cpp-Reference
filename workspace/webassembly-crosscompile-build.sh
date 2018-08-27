#!/usr/bin/env bash

cmake \
  -G "Unix Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake \
  \
  .. && make
