#include "allocator.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numeric>


struct AllocatorInVectorTests : public testing::Test
{
  static constexpr std::size_t N = 10;
  using Key = int;
  std::vector<Key, MyAllocator<Key, N>> vector{};

  void SetUp() override {
    vector.resize(N);
    std::iota(std::begin(vector), std::end(vector), 0);
  }
};

TEST_F(AllocatorInVectorTests, MemoryEnds)
{
  ASSERT_THROW(vector.push_back(0), std::exception);
}

TEST_F(AllocatorInVectorTests, MemoryExactResize)
{
  ASSERT_NO_THROW(vector.resize(N));
}

TEST_F(AllocatorInVectorTests, MemoryResizeToZero)
{
  ASSERT_NO_THROW(vector.resize(0));
}

TEST_F(AllocatorInVectorTests, MemoryEndsForResize)
{
  ASSERT_THROW(vector.resize(11), std::exception);
}

TEST(AllocatorInVectorTest, MemoryEndsForOverResizeFirstTime)
{
  static constexpr std::size_t N = 10;
  std::vector<int, MyAllocator<int, N>> v;

  ASSERT_THROW(v.resize(N+1), std::exception);
}

TEST(AllocatorInVectorTest, MemoryEndsForOverReserveFirstTime)
{
  static constexpr std::size_t N = 10;
  std::vector<int, MyAllocator<int, N>> v;

  ASSERT_THROW(v.reserve(N+1), std::exception);
}
