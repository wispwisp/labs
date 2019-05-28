#include "UnionMatrix.hpp"

int main() {
  UnionMatrix um(10);

  asm("int $3");

  um.unite(0, 1);
  um.unite(1, 2);

  um.unite(4, 3);
  um.unite(5, 4);

  um.unite(3, 6);
  um.unite(2, 5);

  return 0;
}
