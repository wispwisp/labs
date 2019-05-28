#ifndef MY_MATRIX_INDEXER_HPP
#define MY_MATRIX_INDEXER_HPP

#include <tuple>

#include <stdexcept>
#include <exception> // out_of_range

template<class Source>
class MatrixIndexer {
  const Source& source;
  const std::size_t I, J;
public:
  MatrixIndexer(const Source& source_, std::size_t I_, std::size_t J_)
    : source(source_), I(I_), J(J_) {
    if (source.size() != (I * J))
      throw std::out_of_range("Inconsistent dimensions");
  }

  std::size_t get_I() const noexcept {return I;}
  std::size_t get_J() const noexcept {return J;}

  // -> [is_error:bool, index_in_source:size_t]
  auto get_index(std::size_t i, std::size_t j) {
    // Wrong dimensions requested
    if (not(j < J && i < I))
      return std::make_tuple(true, std::size_t{0});

    std::size_t index = (i * I) + j;
    return std::make_tuple(false, index);
  }

  // -> [is_error:bool, index_in_source:size_t]
  auto get_left_neighbor_index(std::size_t i, std::size_t j) {
    if (not(j < J && i < I))
      return std::make_tuple(true, std::size_t{0});

    if (j==0) // first element in a row - error
      return std::make_tuple(true, std::size_t{0});

    std::size_t index = (i * I) + (j - 1);
    return std::make_tuple(false, index);
  }

  // -> [is_error:bool, index_in_source:size_t]
  auto get_right_neighbor_index(std::size_t i, std::size_t j) {
    if (not(j < J && i < I))
      return std::make_tuple(true, std::size_t{0});

    if (j == (J - 1)) // last element in a row - error
      return std::make_tuple(true, std::size_t{0});

    std::size_t index = (i * I) + (j + 1);
    return std::make_tuple(false, index);
  }

  // -> [is_error:bool, index_in_source:size_t]
  auto get_up_neighbor_index(std::size_t i, std::size_t j) {
    if (not(j < J && i < I))
      return std::make_tuple(true, std::size_t{0});

    if (i == 0) // first row, no rows above
      return std::make_tuple(true, std::size_t{0});

    std::size_t index = ((i - 1) * I) + j;
    return std::make_tuple(false, index);
  }

  // -> [is_error:bool, index_in_source:size_t]
  auto get_down_neighbor_index(std::size_t i, std::size_t j) {
    if (not(j < J && i < I))
      return std::make_tuple(true, std::size_t{0});

    if (i == (I - 1)) // last row, no rows above
      return std::make_tuple(true, std::size_t{0});

    std::size_t index = ((i + 1) * I) + j;
    return std::make_tuple(false, index);
  }
};

#endif // MY_MATRIX_INDEXER_HPP
