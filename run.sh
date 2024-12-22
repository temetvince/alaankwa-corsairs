#!/bin/bash

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
scan-build --use-cc=clang make -C build
./build/main
