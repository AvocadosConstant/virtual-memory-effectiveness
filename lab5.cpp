#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <unordered_map>
#include "PageTable.h"

int PAGE_FAULTS = 0;
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

int pageTableSearch(std::vector<PageTable*> &page_tables, int pid, int vpn){
  //search page table
  for (int i = 0; i < page_tables.size(); ++i)
  {
    if(page_tables[i]->getPid() == pid){
      //if found, return
      if(page_tables[i]->lookup(vpn) > -1){
        return page_tables[i]->lookup(vpn);
      }
      //if not found check for space
      else{
        page_tables[i]->addPageFault();
        //if space add to page table
        if(page_tables[i]->isSpace()){
          return page_tables[i]->add(vpn);
        }else{ //if not, it's a bad page fault (not found and no room left in the table)
          return -1;
        }
      }
    }
  }

  std::cout<< "Error: Process not found. Exiting..." << std::endl;
  exit(1);
  return 1;
}

void startProcess(std::vector<PageTable*>& page_tables, int pid, int address_space_size){
  page_tables.push_back(new PageTable(pid, address_space_size));
}

std::unordered_map<int, int> reference(std::vector<PageTable*> &page_tables, std::unordered_map<int, int> tlb, int pid, int vpn){
  //check tlb size
  int full = tlb.size() >= 64;
  int pid_process_mask = pid*1e7 + vpn;

  //search tlb
  std::unordered_map<int,int>::const_iterator found = tlb.find(pid_process_mask);

  if(found == tlb.end()){ //if not found
    int index_in_table = pageTableSearch(page_tables, pid, vpn);
    if(!full){
      tlb.insert(std::make_pair(pid_process_mask, index_in_table));
    }
  }

  return tlb;
}

void terminateProcess(std::vector<PageTable*>& page_tables, int pid){
  for(int i = 0; i < page_tables.size(); ++i){
    if(page_tables[i]->getPid() == pid){
      PAGE_FAULTS += page_tables[i]->getPageFaultNum();
      delete page_tables[i];
      page_tables.erase(page_tables.begin() + i);
    }
  }
}

int main() {
  gettimeofday(&start, NULL);

  std::ifstream file ("outputFile.txt");
  std::string line;
  std::vector< std::string > lines;
  std::vector<PageTable*> page_tables;
  std::unordered_map<int, int> tlb;

  while (getline(file, line)){
    switch(line[0]){
      case 'S': startProcess(page_tables, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'R': tlb = reference(page_tables, tlb, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'T': terminateProcess(page_tables, std::stoi(split(line)[1])); break;
    }
  }

  std::cout << "Num Page Faults: " << PAGE_FAULTS << std::endl;

  gettimeofday(&end, NULL);
  std::cout << "Elapsed Time: " << ((end.tv_sec  - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec)/1000.0) + 0.5) << "ms" << std::endl;

  file.close();
  return 0;
}
