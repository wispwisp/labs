#!/bin/bash

# dpkg -L llvm | grep symbolize
export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer

./tests
