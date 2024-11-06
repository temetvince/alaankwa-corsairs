#!/bin/bash

cmake -B build -S .
scan-build --use-cc=clang make -C build
./build/main
