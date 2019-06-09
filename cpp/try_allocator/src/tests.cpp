#include "allocator.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numeric>

struct AllocatorInSetTests : public testing::Test
{
  static constexpr std::size_t N = 10;
  using Key = int;
  std::set<Key, std::less<Key>, MyAllocator<Key, N>> set{};

  void SetUp() override {
    for (std::size_t i=0; i < N; i++)
      set.insert(i);
  }
};

TEST_F(AllocatorInSetTests, MemoryEnds)
{
  // insert one more value ( > N)
  ASSERT_THROW(set.insert(10), std::bad_alloc);
}

TEST_F(AllocatorInSetTests, MemoryNotEndsElementExists)
{
  // insert one more value, but no memory
  // allocation, because '0' already in set
  ASSERT_NO_THROW(set.insert(0));
}

TEST_F(AllocatorInSetTests, SharedStateAfterMoveMemoryEnds)
{
  decltype(set) moved = std::move(set);

  ASSERT_THROW(moved.insert(99), std::bad_alloc);
}

TEST_F(AllocatorInSetTests, SharedStateAfterMoveMemoryNotEndsElementExists)
{
  decltype(set) moved = std::move(set);

  ASSERT_NO_THROW(moved.insert(0)); // '0' already in set
}

TEST_F(AllocatorInSetTests, SharedStateAfterCopyMemoryEnds)
{
  // When we copy - allocator`s shared states goes also to copy,
  // but then set copy, it ask another N elements for elements in copy
  ASSERT_THROW(decltype(set) copied = set, std::bad_alloc);
}

TEST(AllocatorInSetTest, SharedStateAfterCopyMemoryHalf)
{
  static constexpr std::size_t N = 10;
  static constexpr std::size_t half = N / 2;
  using Key = int;
  std::set<Key, std::less<Key>, MyAllocator<Key, N>> set{};

  for (std::size_t i=0; i < half; i++)
    set.insert(i);

  // When we copy - allocator`s shared states also goes to copy
  // Here for copy allocates exact second half of elements
  decltype(set) copied = set;

  // No more memory for non-existing element
  ASSERT_THROW(copied.insert(999), std::bad_alloc);

  ASSERT_NO_THROW(copied.insert(0)); // '0' already in set
}

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


int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
