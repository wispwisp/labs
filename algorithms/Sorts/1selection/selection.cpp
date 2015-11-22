#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template<typename Cont> Cont sorted(Cont&& c) {

  auto last = std::end(c);
  for(auto outer_it = std::begin(c);
      outer_it != last;
      ++outer_it) {

    auto min_it = outer_it;
    auto inner_it = std::next(outer_it);

    for(; inner_it != last; ++inner_it) {
      if (*inner_it < *min_it) {
	min_it = inner_it ;
      }
    }

    using std::swap;
    swap(*outer_it, *min_it);
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
