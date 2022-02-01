#!/bin/bash

mkdir -p build

COMPILER_FLAGS="-Wall -Wpedantic -O0 -g"

gcc $COMPILER_FLAGS src/main.c -Isrc -o build/__arc

cp build/__arc $HOME/opt/bin/__arc
cp arc $HOME/opt/bin/arc


