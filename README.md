[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![CI](https://github.com/PotatoMaster101/aocpp/actions/workflows/cicd.yml/badge.svg?branch=main)](https://github.com/PotatoMaster101/aocpp/actions/workflows/cicd.yml)

# AoCPP
A C++23 header-only library for working with [Advent of Code](https://adventofcode.com/) challenges.

## Run Tests
```shell
cmake -B build -S .
cmake --build build --config Release
ctest --test-dir build/tests --build-config Release --extra-verbose
```
