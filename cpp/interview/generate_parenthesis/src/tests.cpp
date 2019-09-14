#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "functionality.hpp"

TEST(MainTests, MainTest)
{
  write_file();
  read_file();
  read_file_and_generate_parenthesis();
}

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
