#ifndef MY_functionality_HPP
#define MY_functionality_HPP

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <future>
#include <string>
#include <vector>

template<class T, std::size_t N>
class File {
public:
  using data_type = T;

  File(std::string name_)
    : name(std::move(name_)) {}

  std::size_t size_in_elements() const noexcept {
    return file_size / bytes;
  }

protected:
  std::size_t bytes = sizeof(T);
  std::string name;

  std::size_t file_size = 0;

  std::size_t pos = 0;
  std::array<T, N> buffer{};
};

template<class T, std::size_t N = 10000>
class InFile : public File<T, N> {
public:
  InFile(std::string name_, std::size_t place=0)
    : File<T, N>(std::move(name_)),
      file(this->name, std::ios::binary | std::ios::ate) {

    if (not file.good())
      throw std::logic_error("File error");

    this->file_size = file.tellg();
    file.seekg(place * this->bytes);

    // initial read
    this->file.read((char*)this->buffer.data(), this->bytes * N);
  }

  T read() {
    if (this->pos == this->size_in_elements())
      throw std::logic_error("Wrong file boundary");

    T r = this->buffer[this->pos++];

    if (this->pos == N) {
      if (not this->file.good())
        throw std::logic_error("Wrong file boundary");

      this->file.read((char*)this->buffer.data(), this->bytes * N);
      this->pos = 0;
    }

    return r;
  }

  std::vector<T> read(std::size_t amount) {
    if ((this->pos + amount) > this->size_in_elements())
      throw std::logic_error("Wrong file boundary");

    std::vector<T> values(amount);
    std::size_t i = 0;

    while(i < amount) {
      values[i++] = this->buffer[this->pos++];

      if (this->pos == N) {
        if (not this->file.good())
          throw std::logic_error("Wrong file boundary3");

        this->file.read((char*)this->buffer.data(), this->bytes * N);
        this->pos = 0;
      }
    }

    return values;
  }

  const T& unshifted_read() {
    return this->buffer[this->pos];
  }

private:
  std::ifstream file{};
};

template<class T, std::size_t N = 10000>
class OutFile : public File<T, N> {
public:
  OutFile(std::string name_)
    : File<T, N>(std::move(name_)),
    file(this->name, std::ios::binary | std::ios::ate) {

    if (not file.good())
      throw std::logic_error("File error");

    this->file_size = file.tellp();
    file.seekp(0);
  }

  ~OutFile() {
    if (not flushed)
      this->file.write((char*)this->buffer.data(),
                       this->bytes * this->pos);
  }

  OutFile(const OutFile&) = delete;
  OutFile(OutFile&&) = delete;
  OutFile& operator=(const OutFile&) = delete;
  OutFile& operator=(OutFile&&) = delete;

  void write(const T& t) {
    flush();
    this->buffer[this->pos++] = t;
    flushed = false; // todo
  }

  void write(const std::vector<T>& values) {
    flush();
    file.write((const char*)values.data(), this->bytes * values.size());
  }


private:
  void flush() {
    if (this->pos == N) {
      this->file.write((char*)this->buffer.data(), this->bytes * N);
      this->pos = 0;
      flushed = true;
    }
  }

  bool flushed = true;
  std::ofstream file{};
};


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

    InFile<T> input_file(file_name, lo);
    return input_file.read(hi - lo);
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

    OutFile<T> out_file(fname);
    out_file.write(values);
  }

  void from_auxiliary_to_merged(InFile<T>& aux, OutFile<T>& merged) const {
    merged.write(aux.read());
  }

  void merge(std::size_t lo, std::size_t mid, std::size_t hi) const {
    InFile<T> lhs(make_file_name(lo, mid));
    InFile<T> rhs(make_file_name(mid, hi));
    OutFile<T> merged(make_file_name_by_borders_checking(lo, hi));

    // merge
    std::size_t i = lo, j = mid;
    for (std::size_t k = lo; k < hi; k++) {
      if (i >= mid) {
        from_auxiliary_to_merged(rhs, merged);
        j++;
      } else if (j >= hi) {
        from_auxiliary_to_merged(lhs, merged);
        i++;
      } else if (rhs.unshifted_read() < lhs.unshifted_read()) {
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
