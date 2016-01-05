#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template<typename Iter> Iter partition(Iter l, Iter r) {

  using std::swap;
  Iter i = l, j = std::prev(r);
  while(true) {
    while (*i < *r) ++i; // i`s <= central element
    while (*r < *j) { // j`s >= central element
      if (j == l) break;
      --j;
    }

    if (i >= j) break;
    swap(*i, *j);
  }
  
  swap(*i, *r);

  return i;
}

template<typename Iter> void qsorted(Iter l, Iter r) {
  if (r <= l)
    return;

  Iter i = partition(l, r);
  qsorted(l, std::prev(i));
  qsorted(std::next(i), r);
}

template<typename Cont> Cont sorted(Cont c) {
  if (!c.empty())
    qsorted(std::begin(c), std::prev(std::end(c)));
  return c;
}

int main() {

  std::vector<int> vec = { 18,0,1,12,14,8,19,2,7 };
  vec = sorted(std::move(vec));

  cout << "sorted: ";
  std::copy(std::begin(vec), std::end(vec),
	    std::ostream_iterator<int>(std::cout, " "));
  cout << endl;

  return 0 ;
}
