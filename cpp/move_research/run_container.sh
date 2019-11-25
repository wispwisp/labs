#!/bin/bash

# --gtest_filter=tests.test-exclude_tests.exclude_test
docker run -it --rm --name=my_move_research my/move_research $@
