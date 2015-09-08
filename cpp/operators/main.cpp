#include <string>
#include <iostream>
#include "Oper.hpp"

int main (int argc, char *argv[]) {

  std::string arg;
  if (argc > 1)
    arg = argv[1];

  Oper::Oper<int> a(1);
  Oper::Oper<int> b(5);
  Oper::Oper<int> v(a);

  std::cout
    << a << std::endl
    << b << std::endl
    << v << std::endl;

  return 0 ;
}
