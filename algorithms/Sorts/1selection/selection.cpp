#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template<typename Cont> Cont sorted(Cont&& c) {

  auto last = std::end(c);
  for(auto current = std::begin(c);
      current != last;
      ++current) {

    // find minimum
    auto min = current;
    for(auto it = std::next(current); it != last; ++it) {
      if (*it < *min)
	min = it ;
    }

    // swap current with minimum
    using std::swap;
    swap(*current, *min);
  }

  return c;
}

int main() {

  std::vector<int> vec = { 18,0,1,12,14,8,19,2,7 };
  vec = sorted(std::move(vec));

  cout << "sorted: " << endl;
  std::ostream_iterator<int, char> outIter(std::cout, ", ");
  std::copy(std::begin(vec), std::end(vec), outIter);
  cout << endl;

  return 0 ;
}
