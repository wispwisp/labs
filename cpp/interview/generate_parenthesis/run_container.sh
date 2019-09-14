#!/bin/bash

# --gtest_filter=tests.test-exclude_tests.exclude_test
docker run -it --rm --name=interview_tasks_generate_parenthesis interview_tasks/generate_parenthesis $@
