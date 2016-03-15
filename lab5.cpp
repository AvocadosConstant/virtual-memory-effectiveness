#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

int main() {
  clock_t begin = clock();
  std::ifstream file ("input.txt");
  std::string line;
  std::vector< std::string > lines;

  while (getline(file, line)){
    lines.push_back(line);
  }

  for(std::string l : lines) {
    std::cout << l << std::endl;
  }

  clock_t end = clock();
  std::cout << double (end - begin) / CLOCKS_PER_SEC << std::endl;

  file.close();
  return 0;
}