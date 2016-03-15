#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <string>

std::vector<std::string> split(std::string line){
  std::vector<std::string> ret_vec;
  std::string current;

  for(char& c : line) {
    if (c != ' ') current += c;
    else {
      ret_vec.push_back(current);
      current = "";
    }
  }
  ret_vec.push_back(current);

  return ret_vec;
}

void start(int pid, int address_space_size){
  std::cout << pid << std::endl;
  std::cout << address_space_size << std::endl;
}

void reference(int pid, int vpn){

}

void terminate(int pid){

}

int main() {
  clock_t begin = clock();
  std::ifstream file ("input.txt");
  std::string line;
  std::vector< std::string > lines;

  while (getline(file, line)){
    switch(line[0]){
      case 'S': start(std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'R': reference(std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'T': terminate(std::stoi(split(line)[1])); break;
    }
  }

  std::unordered_map<int, double> tlb, page;

  tlb.insert (std::make_pair<int,double>(17822,6.0)); // move insertion
  tlb.insert (std::make_pair<int,double>(17823,6.0));

  std::cout << "tlb contains:" << std::endl;
  for (auto& x: tlb)
    std::cout << x.first << ": " << x.second << std::endl;

  std::unordered_map<int,double>::const_iterator got = tlb.find(17822);
  if(got == tlb.end()){
    std::cout << "not found";
  }else{
    std::cout << got->first << " is " << got->second;
  }

  std::cout << std::endl;

  clock_t end = clock();
  std::cout << double (end - begin) / CLOCKS_PER_SEC << std::endl;

  file.close();
  return 0;
}