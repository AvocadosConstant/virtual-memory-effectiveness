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

int getPageFaults(std::vector<PageTable*> &page_tables){
  int pageFaults = 0;
  for (int i = 0; i < page_tables.size(); ++i)
  {
    pageFaults += page_tables[i]->getPageFaultNum();
  }

  return pageFaults;
}

void pageTableSearch(std::vector<PageTable*> &page_tables, int pid, int vpn){
  //search page table
  int ref;
  for (int i = 0; i < page_tables.size(); ++i)
  {
    if(page_tables[i]->getPid() == pid){
      //if found break
      if(page_tables[i]->lookup(vpn) == 1){ //probably just do a break and delete print statement
        std::cout << "page found in pagetable!" << std::endl;
      }
      //if not found check for space
      else{
        //if space add to page table
        if(page_tables[i]->isSpace() == 1){
          page_tables[i]->add(vpn);
        }
        //if not, page fault
        else{
          page_tables[i]->addPageFault();
          //std::cout << "page fault!" << std::endl;
        }
      }
    }
    else{
      std::cout<< "process not found!" << std::endl;
      exit(1);
    }
  }
}

void startProcess(std::vector<PageTable*>& page_tables, int pid, int address_space_size){
  page_tables.push_back(new PageTable(pid, address_space_size));
}

std::unordered_map<double, double> reference(std::vector<PageTable*> &page_tables, std::unordered_map<double, double> tlb, int pid, int vpn){
  int full = 0;

  //check tlb size
  if(tlb.size() >= 64){
    full = 1;
  }

  //search tlb
  std::unordered_map<double,double>::const_iterator got = tlb.find(pid);

  if(got == tlb.end()){
    if(full == 0){
        tlb.insert(std::make_pair<double, double>(pid, vpn));
    }
    else{ //if not found (and full?) search page table
          pageTableSearch(page_tables, pid, vpn);
    }
  }else{
    //if found break (this else can be deleted probably)
    std::cout << "found in tlb" << std::endl;
  }
  return tlb;
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
  std::unordered_map<double, double> tlb, page;

  while (getline(file, line)){
    switch(line[0]){
      case 'S': startProcess(page_tables, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'R': tlb = reference(page_tables, tlb, std::stoi(split(line)[1]), std::stoi(split(line)[2])); break;
      case 'T': terminateProcess(page_tables, std::stoi(split(line)[1])); break;
    }
  }

  int pageFaults = getPageFaults(page_tables);
  std::cout << "Num page faults: " << pageFaults << std::endl;
 /* //these are some functions that can be used in the reference section
  tlb.insert(std::make_pair<int,double>(17822,6.0)); // move insertion
  tlb.insert(std::make_pair<int,double>(17823,6.0));

  tlb.insert(std::make_pair<int, double>(pid, vpn));

  std::cout << "tlb contains:" << std::endl;
  for (auto& x: tlb)
    std::cout << x.first << ": " << x.second << std::endl;

  std::unordered_map<int,double>::const_iterator got = tlb.find(pid);

  if(got == tlb.end()){
    pageTableSearch(pid);
  }else{
    std::cout << got->first << " is " << got->second << std::endl;
    return tlb;
  */
  //end here

  gettimeofday(&end, NULL);
  std::cout << "Elapsed Time: " << ((end.tv_sec  - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec)/1000.0) + 0.5) << "ms" << std::endl;

  file.close();
  return 0;
}
