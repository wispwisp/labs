#include "UnionMatrix.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(UnionMatrixTests, IncorrectIndex) {
  UnionMatrix um(10);

  ASSERT_THROW(um.connected(10, 10), std::out_of_range);
}

TEST(UnionMatrixTests, SimpleConnect) {
  // use some array indexes for that algorithm,
  // lets say u have `std::vector<Item> items;`
  // and u need to save and track connections
  // between them. Use `UnionMatrix um(items.size())`
  // And unite necessary items by their indexes.
  UnionMatrix um(10);

  // connect first and sixth item
  um.unite(0, 7);

  ASSERT_TRUE(um.connected(0, 7));
}

TEST(UnionMatrixTests, NoConnection) {
  UnionMatrix um(10);

  um.unite(0, 7);

  ASSERT_FALSE(um.connected(3, 5));
}

TEST(UnionMatrixTests, ConnectionTransitivity) {
  UnionMatrix um(10);

  // if p is connected to q and q is
  // connected to z, then p is connected to z.
  um.unite(0, 7);
  um.unite(7, 9);

  ASSERT_TRUE(um.connected(0, 9));
}

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
