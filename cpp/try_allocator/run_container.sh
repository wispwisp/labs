#!/bin/bash

# --gtest_filter=tests.test-exclude_tests.exclude_test
docker run -it --rm --name=try_allocator try/allocator $@
