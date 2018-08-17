#!/usr/bin/env bash

#this should be done in cmake.. need to work on resrouces scripts
mkdir -p src/resource/ && cp ../resource/* "$_"

#the curl stuff is wrong. shouldb e done in a cmake module
cmake .. -DCMAKE_TOOLCHAIN_FILE=../thirdparty/glfw/CMake/x86_64-w64-mingw32.cmake -DCURL_LIBRARY=/usr/x86_64-w64-mingw32/sys-root/mingw/lib/libcurl.a -DCURL_INCLUDE_DIR=/usr/x86_64-w64-mingw32/sys-root/mingw/include/ && make