@echo off
rem Builds the project and runs it

cmake ..\CMakeLists.txt
cmake --build . --target format
cmake --build .
Debug\main.exe
