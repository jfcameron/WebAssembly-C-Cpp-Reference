#!/usr/bin/env bash

PROJECT_ROOT="$(git rev-parse --show-toplevel)"

function generateAndMoveToProjectWorkspaceSubdirectory()
{
  if (( $# != 1)); then echo "$0 requires 1 args"; exit 1; fi

  BUILD_DIR="$1"

  if [ ! -d "${BUILD_DIR}" ]; then mkdir "${BUILD_DIR}"; fi

  pushd "${BUILD_DIR}"
}

generateAndMoveToProjectWorkspaceSubdirectory 'windows' 

cmake $PROJECT_ROOT \ 
  -DCMAKE_TOOLCHAIN_FILE=../thirdparty/glfw/CMake/x86_64-w64-mingw32.cmake \
  -DCURL_LIBRARY=/usr/x86_64-w64-mingw32/sys-root/mingw/lib/libcurl.a \
  -DCURL_INCLUDE_DIR=/usr/x86_64-w64-mingw32/sys-root/mingw/include/ \ 
  && make
