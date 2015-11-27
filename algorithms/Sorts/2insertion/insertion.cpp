#include <iostream>
#include <iterator>
#include <vector>


using std::cout;
using std::cin;
using std::endl;


template <typename Cont> Cont sorted(Cont&& c) {
  using std::swap;

  // sink minimum
  for (auto i = c.rbegin(); i != c.rend(); ++i) {
    auto p = std::next(i);
    if (*i < *p)
      swap(*i, *p);
  }

  auto first = std::begin(c);
  for (auto i = first + 2; i != std::end(c); ++i) {
    auto j = i;
    auto v = *i;
    while (v < *std::prev(j)) {
      *j = *std::prev(j);
      --j;
    }
    *j = v;
  }

  return c;
}


int main () {

  std::vector<int> vec = { 18,0,1,12,14,8,19,2,7 };
  vec = sorted(std::move(vec));
  
  cout << "sorted: ";
  std::ostream_iterator<int, char> outIter(std::cout, ", ");
  std::copy(std::begin(vec), std::end(vec), outIter);
  cout << endl;

  return 0;
}
