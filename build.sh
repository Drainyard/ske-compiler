#!/bin/bash

mkdir -p build

gcc -g src/main.c -I. -o build/main.out
