#!/bin/bash

if [ "$1" = "linux" ]; then
    cmake -S . -B build-linux \
          -G Ninja \
          -DCMAKE_TOOLCHAIN_FILE=cmake/linux-toolchain.cmake
    cmake --build build-linux

elif [ "$1" = "windows" ]; then
    cmake -S . -B build-windows \
          -G Ninja \
          -DCMAKE_TOOLCHAIN_FILE=cmake/win-toolchain.cmake
    cmake --build build-windows

else
    echo "Usage: ./build.sh [linux | windows]"
fi
