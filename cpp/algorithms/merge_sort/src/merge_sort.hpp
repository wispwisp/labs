#ifndef MY_MERGE_SORT_HPP
#define MY_MERGE_SORT_HPP

#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <iostream>
#endif

namespace merge_sort {
  template<typename T>
  void merge(T& a, T& aux, std::size_t lo, std::size_t mid, std::size_t hi) {
#ifdef DEBUG_PRINT
    {
      std::cout << "merge: ";

      for (std::size_t i=lo; i < mid; i++)
        std::cout << a[i] << ",";

      std::cout << "[" << a[mid] << "],";

      for (std::size_t i=mid + 1; i <= hi; i++)
        std::cout << a[i] << ",";

      std::cout << " -> ";
    }
#endif

    // copy to auxiliary array
    for (std::size_t k = lo; k <= hi; k++)
      aux[k] = std::move(a[k]);

    std::size_t i = lo, j = mid+1;

    for (std::size_t k = lo; k <= hi; k++) {
      if (i > mid)
        a[k] = aux[j++];
      else if (j > hi)
        a[k] = std::move(aux[i++]);
      else if (aux[j] < aux[i])
        a[k] = std::move(aux[j++]);
      else
        a[k] = std::move(aux[i++]);
    }

#ifdef DEBUG_PRINT
    {
      std::cout << "merged: ";
      for (std::size_t q=lo; q <= hi; q++)
        std::cout << a[q] << ",";
      std::cout << "\n";
    }
#endif
  }

  template<typename T>
  void sort(T& a, T& aux, std::size_t lo, std::size_t hi) {
    if (hi <= lo)
      return;

    std::size_t mid = lo + (hi - lo) / 2;

    #ifdef DEBUG_PRINT
        std::cout << "s(a, aux, lo=" << lo
                  << ", mid=" << mid
                  << ", hi=" << hi << ")" << std::endl;
    #endif

    sort(a, aux, lo, mid);
    sort(a, aux, mid+1, hi);

    merge(a, aux, lo, mid, hi);
  }

  template<typename T>
  void sort(T& a) {
    T auxiliary(a.size(), 0);
    sort(a, auxiliary, 0, a.size() - 1);
  }
}

#endif // MY_MERGE_SORT_HPP
