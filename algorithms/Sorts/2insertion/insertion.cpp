#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template <typename T>
T sorted(T&& mas) {
  for (auto outer_it = std::begin(mas);
       outer_it != std::end(mas);
       ++outer_it) {
    auto elem = *outer_it;
    auto inner_it = outer_it;
    for(;inner_it != std::begin(mas);) {
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

  return mas;
}

int main () {

  std::vector<int> mas = { 18,0,1,12,14,8,19,2,7 };
  mas = sorted(std::move(mas));
  
  cout << "sorted mas: " << endl;
  std::ostream_iterator<int, char> outIter(std::cout, ", ");
  std::copy(std::begin(mas), std::end(mas), outIter);
  cout << endl;

  return 0;
}
