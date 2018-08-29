#!/usr/bin/env bash

mkdir xcode && \
pushd xcode && \
cmake \
  ../.. -GXcode
