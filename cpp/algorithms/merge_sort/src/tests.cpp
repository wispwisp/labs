#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "merge_sort.hpp"

#include <algorithm>
#include <numeric> // iota

TEST(MergeTest, Merge) {
  using array_t = std::vector<int>;

  array_t a{-5, 3, 15, 10, 14};
  array_t auxiliary{0, 0, 0, 0, 0};

  ASSERT_TRUE(std::is_sorted(a.cbegin(), std::next(a.cbegin(), 3)));
  ASSERT_TRUE(std::is_sorted(std::next(a.cbegin(), 3), a.cend()));

  merge_sort::merge(a, auxiliary, 0, 2, a.size() - 1);
  ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(SortTest, Sort) {
  std::vector<int> a{2, 15, -5, 3, 2};

  merge_sort::sort(a);
  ASSERT_TRUE(std::is_sorted(a.begin(), a.end()));
}

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
