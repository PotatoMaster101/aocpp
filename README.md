# AoCPP
A C++23 header-only library for working with [Advent of Code](https://adventofcode.com/) challenges.

## Run Tests
```shell
cmake -B build -S .
cmake --build build --config Release
ctest --test-dir build/tests --build-config Release --extra-verbose
```
