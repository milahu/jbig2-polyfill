#!/usr/bin/env bash

mkdir -p build
cd build
cmake ..
make
# ./jbig2_cli input.jbig2 output.bmp
