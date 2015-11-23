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
    
    auto elem = *outer_it;
    auto inner_it = outer_it;
    for(;inner_it != std::begin(c);) {
      if (*(--inner_it) < elem) {
	inner_it++;
	break;
      }
      else
	inner_it++;
      auto temp_it = inner_it;
      *temp_it = *(--inner_it);
    }

    *inner_it = elem;
  }

  return c;
}

int main () {

  std::vector<int> vec = { 18,0,1,12,14,8,19,2,7 };
  vec = sorted(std::move(vec));
  
  cout << "sorted mas:\n";
  std::ostream_iterator<int, char> outIter(std::cout, ", ");
  std::copy(std::begin(vec), std::end(vec), outIter);
  cout << endl;

  return 0;
}
