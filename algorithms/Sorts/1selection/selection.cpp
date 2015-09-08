#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template<typename T> T sorted(T&& mas) {
  auto end = std::end(mas);
  for(auto outer_it = std::begin(mas);
      outer_it != end;
      ++outer_it) {
    auto min_it = outer_it;
    auto inner_it = std::next(outer_it);
    for(; inner_it != end; ++inner_it) {
      if (*inner_it < *min_it) {
	min_it = inner_it ;
      }
    }
    std::swap(*outer_it, *min_it);
  }

  return mas;
}

int main() {

  std::vector<int> mas = { 18,0,1,12,14,8,19,2,7 };
  mas = sorted(std::move(mas));

  cout << "sorted: " << endl;
  std::ostream_iterator<int, char> outIter(std::cout, ", ");
  std::copy(std::begin(mas), std::end(mas), outIter);
  cout << endl;

  return 0 ;
}
