#!/bin/bash

# --gtest_filter=tests.test-exclude_tests.exclude_test
docker run -it --rm --name=interview_tasks_external_merge_sort interview_tasks/external_merge_sort $@
