#include "ThreadStack.hpp"

#include <iostream>
#include <thread>

int main(int argc, char **argv) {

  using dataType = int;
  ThreadStack<dataType> s;

  std::thread t1{ [&s] {
      dataType dataChunk = 20;
      while(dataChunk) {
        s.produceFrom([&dataChunk]{ return dataChunk; });
        --dataChunk;
      }
    }};

  std::thread t2{ [&s] {
      int flag = 0;
      while (flag != 20) {
        s.consumeBy([&flag](dataType i) {
            flag = i;
            std::cout << i << std::endl;
          });
      }
    }};

  t1.join();
  t2.join();
}
