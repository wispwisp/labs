#include "UnionMatrix.hpp"
#include "MatrixIndexer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include <numeric> // reduce, accumulate
// #include <execution>

TEST(MatrixIndexerInitializationTests, InconsistentDimensions) {
  using source_t = std::vector<bool>;

  source_t intersection(10);

  ASSERT_THROW(MatrixIndexer<source_t>(intersection, 5, 5),
               std::out_of_range);  // 5*5 != 10
}

struct MatrixIndexerTests : public testing::Test
{
  using source_t = std::vector<bool>;

  static constexpr std::size_t N = 10;

  MatrixIndexerTests()
    : intersection(N * N, false), mi(intersection, N, N) {};

  source_t intersection;
  MatrixIndexer<source_t> mi;
};

// Test correct indexes
using indexes_and_expected_t = std::tuple<std::size_t, std::size_t, std::size_t>;

struct TestCorrectSourceIndexes : MatrixIndexerTests,
                                  testing::WithParamInterface<indexes_and_expected_t> {};

TEST_P(TestCorrectSourceIndexes, CorrectIndex)
{
  auto [i, j, expected] = GetParam();
  auto [error, source_index] = mi.get_index(i, j);

  ASSERT_FALSE(error);
  EXPECT_EQ(source_index, expected);
}

INSTANTIATE_TEST_CASE_P(Defaut, TestCorrectSourceIndexes,
                        testing::Values(indexes_and_expected_t(0,0,0),
                                        indexes_and_expected_t(9,9,99),
                                        indexes_and_expected_t(0,9,9),
                                        indexes_and_expected_t(1,9,19)));

// Test wrong indexes
using wrong_index_t = std::tuple<std::size_t, std::size_t>;

struct TestWrongSourceIndexes : MatrixIndexerTests,
                                testing::WithParamInterface<wrong_index_t> {};

void unused(std::size_t) {}

TEST_P(TestWrongSourceIndexes, WrongIndex)
{
  auto [i, j] = GetParam();
  auto [error, _] = mi.get_index(i, j);

  unused(_);

  EXPECT_TRUE(error);
}

INSTANTIATE_TEST_CASE_P(Defaut, TestWrongSourceIndexes,
                        testing::Values(wrong_index_t(0, 10),
                                        wrong_index_t(1, 10),
                                        wrong_index_t(10, 9),
                                        wrong_index_t(10, 0)));

// Test percolation
struct PercolationTests : public MatrixIndexerTests
{
  using index_t = std::size_t;

  // use two more node for start/end connection of terminal sites
  UnionMatrix um{intersection.size() + 2};

  const index_t terminal_1 = intersection.size();
  const index_t terminal_2 = intersection.size() + 1;

  std::random_device random_device{};
  std::mt19937_64 generator{random_device()};
  std::uniform_int_distribution<index_t> i_distribution{0, mi.get_I() - 1};
  std::uniform_int_distribution<index_t> j_distribution{0, mi.get_J() - 1};

  void print_intersection() {
    for (std::size_t i=0; i<mi.get_I(); i++) {
      for (std::size_t j=0; j<mi.get_J(); j++) {
        auto [error, index] = mi.get_index(i, j);
        if(error)
          throw std::exception();

        if (intersection.at(index))
          std::cout << " ";
        else
          std::cout << "X";
      }
      std::cout << std::endl;
    }
  }
};

TEST_F(PercolationTests, DISABLED_VisualTest)
{
  for (std::size_t c=0; c<10000000; c++) {
    auto i = i_distribution(generator);
    auto j = j_distribution(generator);

    auto [error, index] = mi.get_index(i, j);
    // std::cout << i << ", " << j << " -> " << index << std::endl;
    ASSERT_FALSE(error);

    intersection.at(index) = true;

    // first line of matrix - connect to terminal
    if (i == 0)
      um.unite(index, terminal_1);

    // last line of matrix - connect to terminal
    else if (i == (mi.get_I() - 1))
      um.unite(index, terminal_2);

    // connect neighbors if site open
    auto [neighbor_error, neighbor_index] = mi.get_left_neighbor_index(i, j);
    if (not neighbor_error && intersection.at(neighbor_index))
      um.unite(index, neighbor_index);

    std::tie(neighbor_error, neighbor_index) = mi.get_right_neighbor_index(i, j);
    if (not neighbor_error && intersection.at(neighbor_index))
      um.unite(index, neighbor_index);

    std::tie(neighbor_error, neighbor_index) = mi.get_up_neighbor_index(i, j);
    if (not neighbor_error && intersection.at(neighbor_index))
      um.unite(index, neighbor_index);

    std::tie(neighbor_error, neighbor_index) = mi.get_down_neighbor_index(i, j);
    if (not neighbor_error && intersection.at(neighbor_index))
      um.unite(index, neighbor_index);

    // repeat until the system percolates
    if (um.connected(terminal_1, terminal_2)) {
      std::cout << "Finish from " << c << " iterations" << std::endl;
      break;
    }
  }

  print_intersection();

  // probability
  // auto sum = std::reduce(std::execution::par_unseq,
  //                        std::cbegin(intersection), std::cend(intersection));

  auto sum = std::accumulate(std::cbegin(intersection), std::cend(intersection), std::size_t{0});
  std::cout << sum / double(intersection.size()) << std::endl;
}

TEST(DISABLED_Simulation, DISABLED_Simulation) {
  static constexpr std::size_t N = 1000;
  using source_t = std::vector<bool>;

  std::random_device random_device{};
  std::mt19937_64 generator{random_device()};
  std::uniform_int_distribution<std::size_t> i_distribution{0, N - 1};
  std::uniform_int_distribution<std::size_t> j_distribution{0, N - 1};

  double acc = 0.0;
  std::size_t amount = 0;

  for (std::size_t k=0; k<100; k++) {
    source_t intersection(N * N, false);

    MatrixIndexer<source_t> mi(intersection, N, N);

    // use two more node for start/end connection of terminal sites
    UnionMatrix um{intersection.size() + 2};

    const std::size_t terminal_1 = intersection.size();
    const std::size_t terminal_2 = intersection.size() + 1;

    bool found = false;

    for (std::size_t c=0; c<1000000; c++) {
      auto i = i_distribution(generator);
      auto j = j_distribution(generator);

      auto [error, index] = mi.get_index(i, j);
      ASSERT_FALSE(error);

      intersection.at(index) = true;

      // first line of matrix - connect to terminal
      if (i == 0)
        um.unite(index, terminal_1);

      // last line of matrix - connect to terminal
      else if (i == (mi.get_I() - 1))
        um.unite(index, terminal_2);

      // connect neighbors if site open
      auto [neighbor_error, neighbor_index] = mi.get_left_neighbor_index(i, j);
      if (not neighbor_error && intersection.at(neighbor_index))
        um.unite(index, neighbor_index);

      std::tie(neighbor_error, neighbor_index) = mi.get_right_neighbor_index(i, j);
      if (not neighbor_error && intersection.at(neighbor_index))
        um.unite(index, neighbor_index);

      std::tie(neighbor_error, neighbor_index) = mi.get_up_neighbor_index(i, j);
      if (not neighbor_error && intersection.at(neighbor_index))
        um.unite(index, neighbor_index);

      std::tie(neighbor_error, neighbor_index) = mi.get_down_neighbor_index(i, j);
      if (not neighbor_error && intersection.at(neighbor_index))
        um.unite(index, neighbor_index);

      // repeat until the system percolates
      if (um.connected(terminal_1, terminal_2)) {
        found = true;
        break;
      }
    }

    if (found) {
      auto sum = std::accumulate(std::cbegin(intersection), std::cend(intersection), std::size_t{0});
      acc += (sum / double(intersection.size()));
      amount++;
    }
  }

  std::cout << "Average result[" << amount << "]: " << acc / amount << std::endl;
}


int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
