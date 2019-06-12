#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "allocator.hpp"

TEST(AllocatorTraitsTest, AllocatorTraitsTest)
{
  using ::testing::Eq;

  using allocator_t = IrretrievableAllocator<int, 10>;

  ASSERT_THAT(std::allocator_traits<allocator_t>::propagate_on_container_copy_assignment::value, Eq(true));
  ASSERT_THAT(std::allocator_traits<allocator_t>::propagate_on_container_move_assignment::value, Eq(true));
  ASSERT_THAT(std::allocator_traits<allocator_t>::propagate_on_container_swap::value, Eq(true));
  ASSERT_THAT(std::allocator_traits<allocator_t>::is_always_equal::value, Eq(false));
}
