#ifndef MY_ALLOC_HPP
#define MY_ALLOC_HPP

#include <memory>
#include <vector>

// #define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <iostream>
#endif


template <class T, std::size_t N>
struct MyAllocator {
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  struct SharedState {
    SharedState(std::size_t sz) : memory(sz) {
#ifdef DEBUG_PRINT
      std::cout << "Shared state created, memory limit: " << sz << std::endl;
#endif
    }

    std::size_t index = 0;
    std::vector<T> memory;
  };

  MyAllocator() : shared_state(std::make_shared<SharedState>(N)) {}

  // rebind allocator to type U
  template <class U>
  struct rebind {
    typedef MyAllocator<U, N> other;
  };

  // return address of values
  pointer address (reference value) const {
    return &value;
  }

  const_pointer address (const_reference value) const {
    return &value;
  }

  // return maximum number of elements that can be allocated
  size_type max_size () const noexcept {
    return shared_state->memory.size();
  }

  // allocate but don't initialize num elements of type T
  pointer allocate(size_type num, const void * = 0) {
    if ((shared_state->index + num) > shared_state->memory.size())
      throw std::bad_alloc();

#ifdef DEBUG_PRINT
    std::cout << "allocate " << num << " element(s)"
              << " of size " << sizeof(T) << std::endl;
#endif

    pointer ret = &shared_state->memory.at(shared_state->index);
    shared_state->index += num;

#ifdef DEBUG_PRINT
    std::cout << "allocated at: " << (void *)ret << std::endl;
    std::cout << "Memory remains: " <<  shared_state->index
              << " Of " << N << std::endl;
#endif

    return ret;
  }

  // initialize elements of allocated storage p with value value
  void construct (pointer p, const T& value) {
    *p = T(value);
  }

  // destroy elements of initialized storage p
  void destroy (pointer p) {
    p->~T();
  }

  // deallocate storage p of deleted elements
  void deallocate(pointer, size_type) {
#ifdef DEBUG_PRINT
    std::cout << "dealocation called\n";
#endif
  }

private:
  std::shared_ptr<SharedState> shared_state;
};

// return that all specializations of this allocator are interchangeable
// template <class T1, class T2>
// bool operator== (const MyAllocator<T1, N>& lhs,
//                  const MyAllocator<T2, N>& rhs) noexcept {
//   return lhs.shared_state == rhs.shared_state;
// }
// template <class T1, class T2>
// bool operator!= (const MyAllocator<T1>& lhs,
//                  const MyAllocator<T2>& rhs) noexcept {
//   return not(lhs == rhs);
// }

#endif // MY_ALLOC_HPP
