#!/usr/bin/env bash

function getPathToScript()
{
    local relativePath=""

    if [ -L $0 ] ; then
        relativePath=$(readlink $0)
    else
        relativePath=$0
    fi

    echo "$(dirname $relativePath)"
}

clear

cd $(getPathToScript)

rm -R lib
rm -R src

cmake \
    -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" \
    -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake \
    -DJFC_BUILD_DOCS=OFF \
    -DJFC_BUILD_TESTS=ON \
    -DJFC_BUILD_APP=ON \
    -DJFC_AUTO_RUN_APP=OFF \
    -DJFC_FORMAT_CODE=OFF \
    \
    .. && make
