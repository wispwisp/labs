#!/bin/bash

# --gtest_filter=tests.test-exclude_tests.exclude_test
docker run -it --rm \
       --name=union_find_percolation_threshold_tests \
       cpp_algorithms_applications/union_find_percolation_threshold_tests $@
