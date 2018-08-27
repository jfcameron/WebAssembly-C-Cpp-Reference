#!/usr/bin/env bash

if [ -z ${1+x} ]; then
    echo -e "build type not specified at arg1; defaulting to release"
    Build_Type=Release 
else
    Build_Type=${1}
fi

cmake .. -DCMAKE_BUILD_TYPE=${Build_Type}  && make
