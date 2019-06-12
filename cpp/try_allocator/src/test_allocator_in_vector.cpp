#include "allocator.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numeric> // iota

using ::testing::Eq;

struct AllocatorInVectorTests : public testing::Test
{
  static constexpr std::size_t N = 10;
  using Key = int;
  std::vector<Key, IrretrievableAllocator<Key, N>> vector{};

  void SetUp() override {
    vector.resize(N);
    std::iota(std::begin(vector), std::end(vector), 0);
  }
};

TEST_F(AllocatorInVectorTests, MemoryEnds)
{
  ASSERT_ANY_THROW(vector.push_back(0));
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
  ASSERT_ANY_THROW(vector.resize(11));
}

TEST(AllocatorInVectorTest, MemoryEndsForOverResizeFirstTime)
{
  static constexpr std::size_t N = 10;
  std::vector<int, IrretrievableAllocator<int, N>> v;

  ASSERT_ANY_THROW(v.resize(N+1));
}

TEST(AllocatorInVectorTest, MemoryEndsForOverReserveFirstTime)
{
  static constexpr std::size_t N = 10;
  std::vector<int, IrretrievableAllocator<int, N>> v;

  ASSERT_ANY_THROW(v.reserve(N+1));
}

#if 0
struct LoggedElement {
  std::size_t* counter;
  std::size_t id;

  LoggedElement(std::size_t* counter_)
    : counter(counter_), id(*counter) {
    std::cout << "I am created [" << (*counter)++ << "]" << std::endl;
  }

  LoggedElement(LoggedElement&& other)
    : counter(other.counter), id(other.id) {
    std::cout << "I am moved [" << (*counter) << "]" << std::endl;
  }

  LoggedElement(const LoggedElement& other)
    : counter(other.counter), id(other.id) {
    std::cout << "I am copied [" << (*counter)++ << "]" << std::endl;
  }

  LoggedElement& operator= (const LoggedElement& other) {
    counter = other.counter;
    id = other.id;
    std::cout << "I am copy-assigned [" << (*counter)++ << "]" << std::endl;
    return *this;
  }

  LoggedElement& operator= (LoggedElement&& other) {
    counter = other.counter;
    id = other.id;
    std::cout << "I am copy-moved [" << (*counter) << "]" << std::endl;
    return *this;
  }

  ~LoggedElement() {
    std::cout << "I am destroed [" << (*counter)-- << "]" << std::endl;
  }
};

std::ostream& operator<< (std::ostream& os, const LoggedElement& l) {
  return os << l.id;
}

TEST(AllocatorInVectorTest, SharedStateAfterMoveMemoryEnds)
{
  std::size_t counter = 0;

  std::cout << "Creating...\n";
  static constexpr std::size_t N = 10;
  std::vector<LoggedElement,
              IrretrievableAllocator<LoggedElement, N> > vector;

  std::cout << "Filling...\n";
  vector.reserve(N);
  for (std::size_t i=0; i<N; i++)
    vector.emplace_back(&counter);

  std::cout << "Moving...\n";
  decltype(vector) moved = std::move(vector);

  for (const auto& item : moved)
    std::cout << item << ',';
  std::cout << std::endl;

  ASSERT_THAT(vector.empty(), Eq(true));

  // uses allocator max_size, and throws not a bad_alloc
  ASSERT_ANY_THROW(moved.emplace_back(&counter));
}
#endif
