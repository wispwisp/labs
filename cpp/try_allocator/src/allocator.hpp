#ifndef MY_ALLOC_HPP
#define MY_ALLOC_HPP

#include <memory>
#include <vector>

#include <cstring> // memcpy

#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <iostream>
#endif

template <class T, std::size_t N>
struct IrretrievableAllocator {

  using value_type = T;

  using propagate_on_container_copy_assignment = std::true_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;

  using is_always_equal = std::false_type;

  ~IrretrievableAllocator() {
    if (memory)
      std::free(memory);
  }

  IrretrievableAllocator()
    : index(0), memory(static_cast<T*>(std::malloc(N * sizeof(T)))) {}

  IrretrievableAllocator(IrretrievableAllocator&& other)
    : index(other.index), memory(other.memory) {

    other.index = 0;
    other.memory = nullptr;
  }

  IrretrievableAllocator(const IrretrievableAllocator& other)
    : index(other.index),
      memory(static_cast<T*>(std::malloc(N * sizeof(T)))) {

    // copy underlying memory (why? its cleared anyway)
    std::memcpy(memory, other.memory, sizeof(T) * index);
  }

  IrretrievableAllocator& operator= (const IrretrievableAllocator& other) {
    if (this != &other) {
      index = other.index;
      memory = static_cast<T*>(std::malloc(N * sizeof(T)));

      // copy underlying memory (why? its cleared anyway)
      std::memcpy(memory, other.memory, sizeof(T) * index);
    }

    return *this;
  }

  IrretrievableAllocator& operator= (IrretrievableAllocator&& other) {
    if (this != &other) {
      index = other.index;
      memory = other.memory;

      other.index = 0;
      other.memory = nullptr;
    }

    return *this;
  }

  // rebind allocator to type U
  // example: rebind from T to node<T> in list container.
  template <class U>
  struct rebind {
    typedef IrretrievableAllocator<U, N> other;
  };

  // return maximum number of elements that can be allocated
  std::size_t max_size() const noexcept {
    return N;
  }

  T* allocate(std::size_t num) {
    std::size_t end = index + num;

    if (end > N)
      throw std::bad_alloc();

    T* ret = memory + index;
    index = end;

#ifdef DEBUG_PRINT
    {
      std::cout << "* allocate " << num << " element(s)"
                << " of size " << sizeof(T) << "; "
                << "allocated at: " << (void *)ret << "; "
                << "Memory remains: " <<  index
                << " Of " << N << std::endl;
    }
#endif

    return ret;
  }

  void deallocate(T*, std::size_t) {
    ; // Irretrievable
  }

  std::size_t index;
  T* memory = nullptr;
};

// compare to check that all specializations of this allocator are interchangeable
template <class T, std::size_t N>
bool operator== (const IrretrievableAllocator<T, N>& lhs,
                 const IrretrievableAllocator<T, N>& rhs) {
  return lhs.memory == rhs.memory;
}

template <class T, std::size_t N>
bool operator!= (const IrretrievableAllocator<T, N>& lhs,
                 const IrretrievableAllocator<T, N>& rhs) {
  return not(lhs == rhs);
}

#endif // MY_ALLOC_HPP
