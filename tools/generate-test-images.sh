#!/usr/bin/env bash

cd "$(dirname "$0")/.."

mkdir -p img

if [ -n "$1" ]; then
  src="$1"
  if ! [ -e "$src" ]; then
    echo "error: no such file: $src"
    exit 1
  fi
  set -x
else
  set -x
  src=img/test.png
  if ! [ -e "$src" ]; then
    magick rose: -scale 400% "$src"
  fi
fi

./tools/compress-jbig2.sh "$src" img/test.jbig2

# ./tools/decompress-jbig2.sh img/test.jbig2 img/test.jbig2.bmp

./build/jbig2_to_bmp img/test.jbig2 img/test.jbig2.bmp
