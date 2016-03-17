#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <unordered_map>
#include "PageTable.h"

struct timeval start, end;

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

void startProcess(std::vector<PageTable*>& page_tables, int pid, int address_space_size){
  page_tables.push_back(new PageTable(pid, address_space_size));
}

void reference(int pid, int vpn){

}

void terminateProcess(std::vector<PageTable*>& page_tables, int pid){
  for(int i = 0; i < page_tables.size(); ++i){
    if(page_tables[i]->getPid() == pid){
      delete page_tables[i];
      page_tables.erase(page_tables.begin() + i);
    }
  }
}

int main() {
  gettimeofday(&start, NULL);

  std::ifstream file ("input.txt");
  std::string line;
  std::vector< std::string > lines;
  std::vector<PageTable*> page_tables;
  std::unordered_map<int, double> tlb, page;

  while (getline(file, line)){
    switch(line[0]){
      case 'S': startProcess(page_tables, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'R': reference(std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'T': terminateProcess(page_tables, std::stoi(split(line)[1])); break;
    }
  }

  //these are some functions that can be used in the reference section
  tlb.insert(std::make_pair<int,double>(17822,6.0)); // move insertion
  tlb.insert(std::make_pair<int,double>(17823,6.0));

  std::cout << "tlb contains:" << std::endl;
  for (auto& x: tlb)
    std::cout << x.first << ": " << x.second << std::endl;

  std::unordered_map<int,double>::const_iterator got = tlb.find(17822);

  if(got == tlb.end()){
    std::cout << "not found";
  }else{
    std::cout << got->first << " is " << got->second << std::endl;
  }
  //end here

  gettimeofday(&end, NULL);
  std::cout << "Elapsed Time: " << ((end.tv_sec  - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec)/1000.0) + 0.5) << "ms" << std::endl;

  file.close();
  return 0;
}
