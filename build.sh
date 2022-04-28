#!/bin/bash

BUILD_DIR=build
EXECUTABLE_NAME=__ske
SCRIPT_NAME=ske

mkdir -p $BUILD_DIR

COMPILER_FLAGS="-Wall -Wpedantic -O0 -g"

gcc $COMPILER_FLAGS src/main.c -Isrc -o $BUILD_DIR/$EXECUTABLE_NAME

cp build/$EXECUTABLE_NAME $HOME/opt/bin/$EXECUTABLE_NAME
cp $SCRIPT_NAME $HOME/opt/bin/$SCRIPT_NAME
