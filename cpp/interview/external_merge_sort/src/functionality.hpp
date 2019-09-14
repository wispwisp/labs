#ifndef MY_functionality_HPP
#define MY_functionality_HPP

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <future>
#include <string>
#include <vector>

template<class T>
class ExternalSort {
 public:
  ExternalSort(std::string input_file_name_,
               std::string output_file_name_)
    : input_file_name(input_file_name_),
      output_file_name(output_file_name_),
      input_file_size(file_size(input_file_name))
  {}

  std::size_t file_size(const std::string& fname) const {
    std::ifstream file(fname, std::ios::binary | std::ios::ate);
    if (not file.good())
      return 0;

    return file.tellg() / bytes;
  }

  void run() const {
    if (input_file_size <= inplace_border)
      inplace_sort(0, input_file_size, output_file_name);
    else
      sort(0, input_file_size);
  }

  bool reset_inplace_border(std::size_t new_sz) {
    if (new_sz <= 2) // least pragmatic border (todo: empirically)
      return false;

    inplace_border = new_sz;
    return true;
  }

private:
  std::size_t bytes = sizeof(T);

  std::string input_file_name;
  std::string output_file_name;

  std::size_t input_file_size;
  std::size_t inplace_border = 2;

  void sort(std::size_t lo, std::size_t hi) const {
    if (lo >= hi)
      return;

    if (hi - lo <= inplace_border)
      return inplace_sort(lo, hi, make_file_name(lo, hi));

    std::size_t mid = lo + ((hi - lo) / 2);

    auto sort_future = std::async(&ExternalSort::sort, this, lo, mid);
    sort(mid, hi);
    sort_future.get();

    merge(lo, mid, hi);
  }

  std::vector<T> read_values(const std::string &file_name,
                             std::size_t lo, std::size_t hi) const {

    std::ifstream input_file(file_name, std::ios::binary);
    input_file.seekg(lo * bytes);

    std::size_t sz = hi - lo;
    std::vector<T> values(sz);

    for (std::size_t i=0; i<sz; i++) {
      input_file.read((char*)&values[i], bytes);

      if (not input_file.good())
        throw std::logic_error("Wrong file boundary");
    }

    return values;
  }

  std::string make_file_name(std::size_t lo,std::size_t hi) const {
    return std::to_string(lo) + "_" + std::to_string(hi);
  }

  std::string make_file_name_by_borders_checking(std::size_t lo,
                                                 std::size_t hi) const {
    if (hi == input_file_size && lo == 0)
      return output_file_name;

    return make_file_name(lo, hi);
  }

  void inplace_sort(std::size_t lo, std::size_t hi,
                    const std::string& fname) const {

    auto values = read_values(input_file_name, lo, hi);
    std::sort(values.begin(), values.end());

    std::ofstream out_file(fname, std::ios::binary);
    for (const auto& v : values)
      out_file.write((const char*)&v, bytes);
  }

  void from_auxiliary_to_merged(std::ifstream& aux,
                                std::ofstream& merged) const {
    T t;
    aux.read((char*)&t, bytes);
    merged.write((const char*)&t, bytes);
  }

  T get_value(std::ifstream& aux) const {
    auto save = aux.tellg();

    T t;
    aux.read((char*)&t, bytes);
    aux.seekg(save);

    return t;
  };

  void merge(std::size_t lo, std::size_t mid, std::size_t hi) const {
    // sub aux-merged files
    std::ifstream lhs(make_file_name(lo, mid), std::ios::binary);
    if (not lhs.good())
      throw std::logic_error("file not exists");

    std::ifstream rhs(make_file_name(mid, hi), std::ios::binary);
    if (not rhs.good())
      throw std::logic_error("file not exists");

    // output file
    auto fname = make_file_name_by_borders_checking(lo, hi);
    std::ofstream merged(fname, std::ios::binary);

    // merge
    std::size_t i = lo, j = mid;
    for (std::size_t k = lo; k < hi; k++) {
      if (i >= mid) {
        from_auxiliary_to_merged(rhs, merged);
        j++;
      } else if (j >= hi) {
        from_auxiliary_to_merged(lhs, merged);
        i++;
      } else if (get_value(rhs) < get_value(lhs)) {
        from_auxiliary_to_merged(rhs, merged);
        j++;
      } else {
        from_auxiliary_to_merged(lhs, merged);
        i++;
      }
    }
  }
};

#if 0
int main() {
  try {
    std::size_t m = 1048576; // 1MB -> 1024KB -> 1048576B
    std::size_t half_of_restriction = 128 / 2;
    std::size_t in_memory_elements_sort_border =
      (m * half_of_restriction) / sizeof(std::uint32_t);

    ExternalSort<std::uint32_t> sort("input", "output");
    sort.reset_inplace_border(in_memory_elements_sort_border);
    sort.run();

  } catch(...) {
    return -1;
  }

  return 0;
}
#endif

#endif // MY_functionality_HPP
