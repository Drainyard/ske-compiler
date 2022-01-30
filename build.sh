#!/bin/bash

mkdir -p build

COMPILER_FLAGS="-Wall -Wpedantic -O0 -g"

gcc $COMPILER_FLAGS src/main.c -Isrc -o build/arc

cp build/arc $HOME/opt/bin/arc


