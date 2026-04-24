#!/bin/sh

cd "$(dirname "$0")"

mkdir -p build-wasm
cd build-wasm
emcmake cmake -S ..
cmake --build . --verbose
