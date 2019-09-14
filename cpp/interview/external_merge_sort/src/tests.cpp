#include "functionality.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <random>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <cstdint>
#include <initializer_list>

#include <experimental/filesystem>

void clean_directory() {
  namespace fs = std::experimental::filesystem;
  for (const auto& x : fs::directory_iterator(fs::path("./"))) {
    if (x.path() != "./tests")
      fs::remove(x.path());
  }
}

using ::testing::Eq;

struct ExternalSortBaseTest : public testing::Test {
  const std::string input_file_name{"input"};
  const std::string output_file_name{"output"};

  void write_binary_file(const std::string& fname,
                         std::initializer_list<std::uint32_t> list) {

    std::ofstream outfile(fname, std::ios::binary);
    for (const auto& n : list)
      outfile.write((const char*)&n, sizeof(std::uint32_t));
  }

  template<typename T>
  void read_binary_file(const std::string &filename,
                        std::vector<T> &out) {
    // open file and set position
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (not file.good())
      throw std::logic_error("file not exists");

    std::streampos begin = 0;
    std::streampos end = file.tellg();

    // set to start
    file.seekg(0);

    std::size_t sz = end / sizeof(T);
    out.resize(sz);

    for (std::size_t i=0; i<sz; i++) {
      file.read((char*)&out[i], sizeof(T));
      begin += sizeof(T);
    }

    // postcondition check
    if (begin != end)
      throw std::logic_error("Subfile not processed entirely");
  }

  std::vector<std::uint32_t> read_values(const std::string& fname) {
    std::vector<std::uint32_t> values;
    read_binary_file(fname, values);
    return values;
  }

  void print_values(const std::string& fname) {
    std::vector<std::uint32_t> values;

    std::cout << fname << ": ";
    read_binary_file(fname, values);
    for (std::size_t i=0; i<values.size(); i++)
      std::cout << values[i] << ",";
    std::cout << "\n";
  }

  void assert_correctness(const std::vector<std::uint32_t>& values,
                          const std::initializer_list<std::uint32_t>& list) {

    std::vector<std::uint32_t> expected(list);
    std::sort(expected.begin(), expected.end());

    ASSERT_THAT(values, Eq(expected));
  }

  virtual void TearDown() override {
    clean_directory();
    Test::TearDown();
  }
};

TEST_F(ExternalSortBaseTest, SomeValues)
{
  std::initializer_list<std::uint32_t> list =
    {
      5, 0, 11, 2, 2, 8, 147, 257, 0, 0,
      13, 147, 142, 222, 654, 871, 248,
    };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, SortedValues)
{
  std::initializer_list<std::uint32_t> list =
    {
      1,2,3,4,5,6,7,8,9,10
    };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, ReversedSortedValues)
{
  std::initializer_list<std::uint32_t> list =
    {
      21,20,19,18,17,10,5,4,3,2,1
    };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, Empty)
{
  std::ofstream outfile(output_file_name, std::ios::binary | std::ios::trunc);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, {});
}

TEST_F(ExternalSortBaseTest, OneValue)
{
  std::initializer_list<std::uint32_t> list{ 42 };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, TwoValues)
{
  std::initializer_list<std::uint32_t> list{ 42, 12 };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, BiggerThanMinimalBorder)
{
  std::initializer_list<std::uint32_t> list{ 42, 0, 12 };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, BiggerThanMinimalBorderWithBorderReseted)
{
  std::initializer_list<std::uint32_t> list{ 42, 0, 12, 4 };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.reset_inplace_border(3);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, Zeroes)
{
  std::initializer_list<std::uint32_t> list{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);
}

TEST_F(ExternalSortBaseTest, Ones)
{
  std::initializer_list<std::uint32_t> list{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  };

  write_binary_file(input_file_name, list);

  ExternalSort<std::uint32_t> sort(input_file_name, output_file_name);
  sort.run();

  auto values = read_values(output_file_name);
  assert_correctness(values, list);

  // print_values(output_file_name);
}

TEST_F(ExternalSortBaseTest, Randoms)
{
  using T = std::uint32_t;
  std::size_t N = 4455;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::normal_distribution<double> generator(42, 20);

  std::vector<T> expected(N);
  {
    std::ofstream file(input_file_name, std::ios::binary);

    for (std::size_t i=0; i<N; i++) {
      expected[i] = static_cast<T>(generator(gen));
      file.write((const char*)&expected[i], sizeof(T));
    }
  }

  ExternalSort<T> sort(input_file_name, output_file_name);
  sort.reset_inplace_border(64);
  sort.run();

  std::vector<T> values;
  read_binary_file(output_file_name, values);

  std::sort(expected.begin(), expected.end());
  ASSERT_THAT(values, Eq(expected));

  // std::cout << output_file_name << ": ";
  // read_binary_file(output_file_name, values);
  // for (std::size_t i=0; i<values.size(); i++)
  //   std::cout << values[i] << ",";
  // std::cout << "\n";
}

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

