#!/usr/bin/env bash

mkdir -p src/resource/ && cp ../resource/* "$_"

if [ -z ${1+x} ]; then
    echo -e "build type not specified at arg1; defaulting to release"
    Build_Type=Releas   
else
    Build_Type=${1}
fi

cmake .. -DCMAKE_BUILD_TYPE=${Build_Type}  && make
