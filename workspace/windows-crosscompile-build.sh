#!/usr/bin/env bash

mkdir -p src/resource/ && cp ../resource/* "$_"

cmake .. -DCMAKE_TOOLCHAIN_FILE=../thirdparty/glfw/CMake/x86_64-w64-mingw32.cmake && make