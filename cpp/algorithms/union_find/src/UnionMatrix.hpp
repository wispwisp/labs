#ifndef MY_UNION_MARTIX_HPP
#define MY_UNION_MARTIX_HPP

#include <vector>
#include <numeric> // iota

#include <stdexcept>
#include <exception> // out_of_range

// In the beginning we have array of consecutive indexes.
// index: 0,1,2,3,4,5,6,7,8,9 - array[0...9]
// value: 0,1,2,3,4,5,6,7,8,9 - i.e array[5] == 5

// Connection is denoted by having same root
// By definition each element connected to itself
// - In begining: array[5] == 5.
// - And same: root(5) == root(5)

// When we connect two indexes, we set one index
// root to another index root (In case of nonoptimized
// version first index to second)

// In code below we use optimized algorithm.
// So we keep track for each subtree size.

/*

| origin:
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   1,1,1,1,1,1,1,1,1,1
indexes[index]: 0,1,2,3,4,5,6,7,8,9

| unite(0, 1): -> (i=0,j=1)
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   2,1,1,1,1,1,1,1,1,1
indexes[index]: 0,0,2,3,4,5,6,7,8,9
                s ^
visual:
   0 2 3 4 5 6 7 8 9
  /
 1


| unite(1, 2): -> (i=0,j=2)
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   3,1,1,1,1,1,1,1,1,1
indexes[index]: 0,0,0,3,4,5,6,7,8,9
                s   ^
visual:
   0   3 4 5 6 7 8 9
  / \
 1   2

| unite(4, 3): -> (i=4,j=3)
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   3,1,1,1,2,1,1,1,1,1
indexes[index]: 0,0,0,4,4,5,6,7,8,9
                      ^ s
visual:
   0      4 5 6 7 8 9
  / \    /
 1   2  3

| unite(5, 4): -> (i=5,j=4)
-- beacause of sizes comapre we always append 5-tree
-- to 4-3-tree (it is smaller)
-- so it means: unite(5, 4) == unite(4, 5)
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   3,1,1,1,3,1,1,1,1,1
indexes[index]: 0,0,0,4,4,4,6,7,8,9
                        s ^
visual:
   0      4   6 7 8 9
  / \    / \
 1   2  3   5

| unite(3, 6): -> (i=4,j=6)
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   3,1,1,1,4,1,1,1,1,1
indexes[index]: 0,0,0,4,4,4,4,7,8,9
                        s   ^
visual:
   0      4     7 8 9
  / \    / \ \
 1   2  3   5 6

| unite(2, 5): -> (i=0,j=4)
index:          0,1,2,3,4,5,6,7,8,9
sizes[index]:   3,1,1,1,7,1,1,1,1,1
indexes[index]: 4,0,0,4,4,4,4,7,8,9
                ^       s
visual:
          4     7 8 9
       / / \ \
      0 3   5 6
     / \
    1   2
*/

// also we have path compression optimization in root()
// set each node in path point to its grandparent
// `indexes[i] = indexes[indexes[i]];`
// It is not shown in example abowe

class UnionMatrix {
  std::vector<std::size_t> indexes;
  std::vector<std::size_t> sizes;

  // chase parent pointers until reach root
  // (depth of i array accesses)
  std::size_t root(std::size_t i) {
    while ( i != indexes[i] ) {

      // Make every other node in path point to its
      // grandparent (thereby halving path length).
      indexes[i] = indexes[indexes[i]];
      i = indexes[i];
    }

    return i;
  }

  bool is_index_correct(std::size_t index) const noexcept {
    return index < indexes.size();
  }

  void check_index(std::size_t index) const {
    if (not is_index_correct(index))
      throw std::out_of_range("incorrect index");
  }

public:
  UnionMatrix(std::size_t N)
    : indexes(N), sizes(N, 1) {
    std::iota(std::begin(indexes), std::end(indexes), 0);
  }

  bool connected(std::size_t p, std::size_t q) {
    check_index(p);
    check_index(q);
    return root(p) == root(q);
  }

  void unite(std::size_t p, std::size_t q) {
    check_index(p);
    check_index(q);

    int i = root(p);
    int j = root(q);

    if (i == j)
      return;

    if (sizes[i] < sizes[j]) {
      indexes[i] = j;
      sizes[j] += sizes[i];
    } else {
      indexes[j] = i;
      sizes[i] += sizes[j];
    }
  }
};

#endif // MY_UNION_MARTIX_HPP
