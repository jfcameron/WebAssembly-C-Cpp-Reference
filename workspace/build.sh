#!/usr/bin/env bash
git clean -fxd;
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" \
      -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/incoming/cmake/Modules/Platform/Emscripten.cmake \
      .. && \
make
