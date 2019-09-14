#ifndef MY_functionality_HPP
#define MY_functionality_HPP

#include <iostream>
#include <fstream>
#include <string>

void write_file() {
  std::ofstream outfile("input.txt");
  outfile << "4\n";
}

void read_file() {
  static const std::string file_name = "input.txt";

  std::ifstream file(file_name);

	while (!file.eof()) {
    std::string str;
		std::getline(file, str);

		if (not str.empty()) {
      std::cout << str << std::endl;
    }
	}
}

std::string get_line(std::ifstream& file) {
  std::string str;
  std::getline(file, str);

  return str;
}

void generate(std::size_t open, std::size_t closed,
              std::size_t n, std::string cur = "") {

  if (cur.size() == 2*n) {
    std::cout << cur << std::endl;
    return;
  }

  if (open < n)
    generate(open + 1, closed, n, cur + "(");

  if (closed < open)
    generate(open, closed + 1, n, cur + ")");
}

void read_file_and_generate_parenthesis() {
  static const std::string file_name = "input.txt";

  std::ifstream file(file_name);

  // first line is size of input
  std::size_t n = 0;

  if (not file.eof()) {
    std::string str = get_line(file);

    if (not str.empty()) {
      n = std::stoi(str);
    }
  }

  if (n == 0)
    return;

  generate(0,0,n);
}

#if 0
int main() {
  read_file_and_generate_parenthesis();
  return 0;
}
#endif

#endif // MY_functionality_HPP
