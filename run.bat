@echo off

cmake -B build -S .
scan-build --use-cc=clang make -C build
Debug\main.exe
