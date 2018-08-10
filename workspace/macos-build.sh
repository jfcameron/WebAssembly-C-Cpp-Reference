#!/usr/bin/env bash

mkdir -p src/resource/ && cp ../resource/* "$_"

cmake ..&&make
