#!/bin/bash

mkdir -p build

gcc -g -O0 src/main.c -Isrc -o build/main.out
