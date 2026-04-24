#!/usr/bin/env bash

set -eux

# lossy
jbig2 "$1" >"$2"

# lossless
# FIXME Refinement broke in recent releases since it's rarely used
# https://github.com/agl/jbig2enc/issues/137
# jbig2 --symbol-mode --refine "$1" >"$2"
# jbig2 --pdf -t 0.97 "$1" >"$2"
# jbig2 -t 0.97 "$1" >"$2"
# jbig2 -t 0.40 "$1" >"$2"
