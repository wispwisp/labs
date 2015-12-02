#include <iostream>
#include <iterator>
#include <vector>


template <typename Cont> Cont sorted(Cont&& c) {
  using std::swap;

#ifdef MY_WITH_SIGNAL_VAULE
  // sink minimum (signal value - no check for last element...
  // in next cycle... j < p will trigger anyway on first element)
  auto min = std::begin(c);
  for (auto i = std::next(min); i != std::end(c); ++i) {
    if (*i < *min)
      min = i;
  }
  swap(*std::begin(c), *min);

  // ins sort:
  for (auto i = std::next(std::begin(c)); i != std::end(c); ++i) {

    auto j = i;
    auto p = std::prev(j);
    while (*j < *p) {
      swap(*j, *p);
      --j;
      --p;
    }
  }


#else // with check for first element
  auto first = std::begin(c);
  for (auto i = first; i != std::end(c); ++i) {

    auto j = i;
    auto p = std::prev(j);
    while ((j != first) &&
	   (*j < *p)) {
      swap(*j, *p);
      --j;
      --p;
    }
  }
#endif

  return c;
}


int main () {

  std::vector<int> vec = { 18,0,1,12,14,8,19,2,7 };
  vec = sorted(std::move(vec));
  
  std::cout << "sorted: ";
  std::ostream_iterator<int, char> outIter(std::cout, ", ");
  std::copy(std::begin(vec), std::end(vec), outIter);
  std::cout << std::endl;

  return 0;
}
