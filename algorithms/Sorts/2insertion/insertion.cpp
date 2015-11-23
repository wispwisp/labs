#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template <typename Cont> Cont sorted(Cont&& c) {
  for (auto outer_it = std::begin(c);
       outer_it != std::end(c);
       ++outer_it) {
    ; // todo
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
