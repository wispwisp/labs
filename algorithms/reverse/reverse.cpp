#include <iterator>
#include <iostream>
#include <string>

template<typename IT>
constexpr void reverse(IT b, IT e) noexcept {
  if (b >= --e)
    return;
  std::iter_swap(b, e);
  reverse(++b, e);
}

template<typename T>
constexpr T reverse(T t) noexcept {
  reverse(std::begin(t), std::end(t));
  return t;
}

/*
template<typename T>
T reverse(T t) {
  if (t.empty()) return t;
  return t.back() + reverse(std::string(std::begin(t), std::prev(std::end(t))));
}
*/

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << argv[0] << " [string]\n";
    return -1;
  }

  std::string str{ argv[1] };
  std::cout << reverse(str) << std::endl;
}
