#!/bin/bash

# --gtest_filter=tests.test-exclude_tests.exclude_test
docker run -it --rm --name=merge_sort cpp_algorithms/merge_sort $@
