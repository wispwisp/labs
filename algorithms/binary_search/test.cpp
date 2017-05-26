#include "binary_search_in_range.hpp"
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <algorithm>

BOOST_AUTO_TEST_SUITE(TestBinarySearchInRange)

static const std::vector<unsigned> big_sample {
  0, 7, 19, 27, 189, 630, 641, 642, 648, 1341, 1359,    // [10]
  1360, 1372, 2146, 2164, 2182, 2860, 2861, 2872, 2874, // [19]
  2908, 2911, 3372, 3378, 3669, 3670, 3675, 3747, 3811,
  3851, 3893, 3901, 3937, 3945, 3972, 3977, 3998, 4016,
  4029, 4048, 4056, 4249, 4718, 4735, 4739, 5480, 5501,
  5503, 5511, 6324, 6343, 6345, 6360, 7029, 7036, 7043,
  7080, 7082, 7518, 7524, 7820, 7821, 7827, 7828, 7911,
  7989, 8039, 8086, 8095, 8136, 8146, 8183, 8189, 8213,
  8230, 8237, 8247, 8249, 8250, 8409, 8748, 8758, 8759,
  8763, 9360, 9369, 9370, 9374, 9981, 9990, 9991, 9992,
  9996, 10533, 10534, 10535, 10538, 10539, 10556, 10558 // [99]
}; // .size() == 100

BOOST_AUTO_TEST_CASE(TestFirst)
{
  BOOST_ASSERT(std::is_sorted(big_sample.cbegin(), big_sample.cend()));
  const auto i = my::binary_search_range(big_sample, 0u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 0);
}

BOOST_AUTO_TEST_CASE(TestFirstInRange)
{
  BOOST_ASSERT(std::is_sorted(big_sample.cbegin(), big_sample.cend()));
  const auto i = my::binary_search_range(big_sample, 3u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 0);
}

BOOST_AUTO_TEST_CASE(TestFirstInRangeNext)
{
  BOOST_ASSERT(std::is_sorted(big_sample.cbegin(), big_sample.cend()));
  const auto i = my::binary_search_range(big_sample, 7u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 1);
}

BOOST_AUTO_TEST_CASE(TestMiddleInRange)
{
  BOOST_ASSERT(std::is_sorted(big_sample.cbegin(), big_sample.cend()));
  const auto i = my::binary_search_range(big_sample, 2873u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 18);
}

BOOST_AUTO_TEST_CASE(TestLastElement)
{
  BOOST_ASSERT(std::is_sorted(big_sample.cbegin(), big_sample.cend()));
  const auto i = my::binary_search_range(big_sample, 10558u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 99);
}

BOOST_AUTO_TEST_CASE(TestEven)
{
  std::vector<unsigned> sample {
    0,  7,   19, 27,  189, 630,  641, 642
// [0] [1]  [2]  [3]  [4]  [5]   [6]  [7]
// _______  ________  ________   ________
  };

  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));

  auto i = my::binary_search_range(sample, 641u);

  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 6);
}

BOOST_AUTO_TEST_CASE(TestEvenLastElement)
{
  std::vector<unsigned> sample {
    0,  7,   19, 27,  189, 630,  641, 642
// [0] [1]  [2]  [3]  [4]  [5]   [6]  [7]
// _______  ________  ________   ________
  };

  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));

  auto i = my::binary_search_range(sample, 642u);

  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 7);
}

BOOST_AUTO_TEST_CASE(TestOdd)
{
  std::vector<unsigned> sample {
    0,  7,  19,   27, 189, 630,  641
// [0] [1]  [2]  [3]  [4]  [5]   [6] [X]
// _______  ________  ________   _______
  };

  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));

  auto i = my::binary_search_range(sample, 640u);

  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 5);
}

BOOST_AUTO_TEST_CASE(TestOddLastElement)
{
  std::vector<unsigned> sample {
    0,  7,  19,   27, 189, 630,  641
// [0] [1]  [2]  [3]  [4]  [5]   [6] [X]
// _______  ________  ________   _______
  };

  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));

  auto i = my::binary_search_range(sample, 641u);

  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 6);
}

BOOST_AUTO_TEST_CASE(TestZero)
{
  std::vector<unsigned> sample{6, 7, 19, 27, 189, 630, 641};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 0u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestEmpty)
{
  std::vector<unsigned> sample{};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 42u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestOneElementFounded)
{
  std::vector<unsigned> sample{1};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 1u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 0);
}

BOOST_AUTO_TEST_CASE(TestOneElementNotFoundedLow)
{
  std::vector<unsigned> sample{1};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 0u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestOneElementNotFoundedHigh)
{
  std::vector<unsigned> sample{1};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 2u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestTwoElementFoundedHigh)
{
  std::vector<unsigned> sample{1,5};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 5u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 1);
}

BOOST_AUTO_TEST_CASE(TestTwoElementFoundedLow)
{
  std::vector<unsigned> sample{1,5};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 1u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 0);
}

BOOST_AUTO_TEST_CASE(TestTwoElementNotFoundedLow)
{
  std::vector<unsigned> sample{1, 5};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 0u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestTwoElementNotFoundedHigh)
{
  std::vector<unsigned> sample{1,5};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 9u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestThreeElementFoundedHigh)
{
  std::vector<unsigned> sample{1,5,24};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 24u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 2);
}

BOOST_AUTO_TEST_CASE(TestThreeElementFoundedMiddle)
{
  std::vector<unsigned> sample{1,5,24};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 5u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 1);
}

BOOST_AUTO_TEST_CASE(TestThreeElementFoundedLow)
{
  std::vector<unsigned> sample{1,5,24};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 1u);
  BOOST_ASSERT(i);
  BOOST_CHECK(*i == 0);
}

BOOST_AUTO_TEST_CASE(TestThreeElementNotFoundedLow)
{
  std::vector<unsigned> sample{1,5,24};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 0u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_CASE(TestThreeElementNotFoundedHigh)
{
  std::vector<unsigned> sample{1,5,24};
  BOOST_ASSERT(std::is_sorted(sample.cbegin(), sample.cend()));
  auto i = my::binary_search_range(sample, 42u);
  BOOST_CHECK(not i);
}

BOOST_AUTO_TEST_SUITE_END()
