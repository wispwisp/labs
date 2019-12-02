#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;

#ifdef _GLIBCXX_DEBUG
TEST(TestOutOfRange, TestOutOfRange)
{
  std::vector<int> v{9};
  v.reserve(2);
  std::cout << v[1] << std::endl;
}
#endif

#ifndef _GLIBCXX_DEBUG
const std::string& make_str() {
  const std::vector<std::string> strs {
    "str1",
    "str2",
  };

  return strs[0];
}

TEST(TestOutOfRange, TestOutOfRange2)
{
  const auto& s = make_str();
  std::cout << s << std::endl;
}
#endif

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
