#ifndef MY_BINARY_SEARCH_HPP
#define MY_BINARY_SEARCH_HPP

#include <boost/optional.hpp>

namespace my {

  /// Excluding last element, C[.size() - 1] index is equal to C[.size() - 2]
  template<typename C, typename V>
  auto binary_search_range(const C& c, const V& v)
    -> boost::optional<typename C::size_type> {

    // Todo concept for unsigned ?
    // Find general for signed/unsigned algorithm ?

    if (c.empty())
      return boost::none;

    using size = typename C::size_type;

    size low = 0;
    size i = 0;
    size high = c.size();

    while (low <= high) {

      i = (low + high) / 2;

      // Is in range? (i, i+1)
      if((i < c.size() - 1) && (v >= c[i] && v < c[i + 1]))
        return i;

      if (v == c[i])
        return i;
      else if (c[i] > v && i != 0)
        high = i - 1;
      else if (i < c.size() - 1)
        low = i + 1;
      else break;
    }

    return boost::none;
  }
}

#endif // MY_BINARY_SEARCH_HPP
