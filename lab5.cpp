#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <unordered_map>
#include "PageTable.h"
#include "TLB.h"

struct timeval start, end;

std::vector<std::string> split(std::string line){
  std::vector<std::string> ret_vec;
  std::string current;

  for(char& c : line) {
    if (c != '\t') current += c;
    else {
      ret_vec.push_back(current);
      current = "";
    }
  }
  ret_vec.push_back(current);

  return ret_vec;
}

bool pageTableSearch(std::vector<PageTable*> &page_tables, int pid, int vpn){
  //search page table
  for (int i = 0; i < page_tables.size(); ++i)
  {
    if(page_tables[i]->getPid() == pid){
      //if found, return
      if(page_tables[i]->lookup(vpn) > -1){
        return true;
      }
      //if not found check for space
      else{
        page_tables[i]->replace(vpn);
        return false;
      }
    }
  }

  std::cout<< "Error: Page Table for specified PID not found. Exiting..." << std::endl;
  exit(1);
  return false;
}

void startProcess(std::vector<PageTable*>& page_tables, int pid, int address_space_size){
  page_tables.push_back(new PageTable(pid, address_space_size));
}

int referenceTLB(std::vector<PageTable*> &page_tables, TLB& tlb, int pid, int vpn){
  bool found = false;

  if (tlb.search(pid, vpn) < 0) {
    found = pageTableSearch(page_tables, pid, vpn);
    tlb.insert(pid, vpn);
  }

  return (found) ? 0 : 1;
}

int referenceNoTLB(std::vector<PageTable*> &page_tables, TLB& tlb, int pid, int vpn){
  return pageTableSearch(page_tables, pid, vpn);
}

void terminateProcess(std::vector<PageTable*>& page_tables, int pid){
  for(int i = 0; i < page_tables.size(); ++i){
    if(page_tables[i]->getPid() == pid){
      delete page_tables[i];
      page_tables.erase(page_tables.begin() + i);
    }
  }
}

int main(int argc, char** argv) {
  gettimeofday(&start, NULL);

  std::ifstream file ("outputFile.txt");
  std::string line;
  std::vector< std::string > lines;
  std::vector<PageTable*> page_tables;
  int page_faults = 0;
  TLB tlb;
  bool useTLB = (argc > 1 && strcmp(argv[1], "-t") == 0);

  while (getline(file, line)){
    if (useTLB){
      switch(line[0]){
        case 'S': startProcess(page_tables, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
        case 'R': page_faults += referenceTLB(page_tables, tlb, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
        case 'T': terminateProcess(page_tables, std::stoi(split(line)[1])); break;
      }
    }else{
      switch(line[0]){
        case 'S': startProcess(page_tables, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
        case 'R': page_faults += referenceNoTLB(page_tables, tlb, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
        case 'T': terminateProcess(page_tables, std::stoi(split(line)[1])); break;
      }
    }
  }

  std::cout << "Num Page Faults: " << page_faults << std::endl;

  gettimeofday(&end, NULL);
  std::cout << "Elapsed Time: " << ((end.tv_sec  - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec)/1000.0) + 0.5) << "ms" << std::endl;

  file.close();
  return 0;
}
