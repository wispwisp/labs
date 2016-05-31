#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>

#include <cstdlib>
#include <cctype>


void foolProtect(const std::string& str) {
  if (str.size() > 3)
    throw std::logic_error("Its very big, man, sorry");
}


bool isEndedBySizeSpecificator(const std::string& str) {
  if (str.size() < 2)
    return false;

  auto it = std::prev(std::end(str));
  if (*it != 'B')
    return false;

  --it;
  return *it == 'K' || *it == 'M' || *it == 'G';
}


unsigned parseSize(std::string str) {
  if (str.size() < 3
      || not isEndedBySizeSpecificator(str))
    throw std::logic_error("Wrong size parameter");

  int multiplier = 1;
  switch (str[str.size() - 2]) {
  case 'K': multiplier = 1024; break;
  case 'M': multiplier = (1024*1024); break;
  case 'G':
    foolProtect(str);
    multiplier = (1024*1024*1024);
    break;
  }

  str[str.size() - 2] = 0; // remove size qualifier from str
  return std::atoi(str.c_str()) * multiplier;
}


int main(int argc, char** argv) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << "<file name> <file size in {KB,MB,GB}>\n";
    return -1;
  }

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<char> dis;

  std::ofstream file(argv[1]);

  auto left = parseSize(argv[2]);

  while(left) {
    char generated = dis(gen);
    if (std::isgraph(generated)) {
      file << generated;
      left--;
    }
  }

  return 0;
}


//g++ -std=c++11 createRandomSymbolsFile.cpp && ./a.out a.txt 10KB && du -hs a.txt && hexdump -C ./a.txt | tail
//g++ -std=c++11 createRandomSymbolsFile.cpp && ./a.out a.txt 10KB && du -hs a.txt 
//g++ -std=c++11 createRandomSymbolsFile.cpp && ./a.out a.txt 10KB
