#!/bin/bash

set -e

export CC=clang

if [ "$1" == "-d" ]; then
    export BUILD_DIR="debug-build"
    BUILD_TYPE="Debug"
else
    export BUILD_DIR="release-build"
    BUILD_TYPE="Release"
fi

mkdir -p $BUILD_DIR

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -S . -B "$BUILD_DIR"

cmake --build "$BUILD_DIR"
