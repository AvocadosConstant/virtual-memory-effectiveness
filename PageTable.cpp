#include "PageTable.h"

PageTable::PageTable(int pid, int size){
  this->pid = pid;
  this->size = size;
  this->table = new int[size];
  this->pageFaultNum = 0;

  for (int i = 0; i < size; ++i)
  {
    table[i] = 0;
  }
}

int PageTable::lookup(int reference){
  for(int i = 0; i < this->size; ++i){
    if(this->table[i] == reference){
      return 1;
    }
  }
  return 0;
}

int PageTable::getPid(){
  return this->pid;
}

int PageTable::isSpace(){
  for (int i = 0; i < this->size; ++i)
  {
    if(this->table[i] == 0){
      return 1; //found a space
    }
  }
  return 0; //no space
}

void PageTable::add(int vpn){
  for (int i = 0; i < this->size; ++i)
  {
    if(this->table[i] == 0){
      this->table[i] = vpn;
      return;
    }
  }
}

void PageTable::addPageFault(){
  this->pageFaultNum++;
  return;
}

int PageTable::getPageFaultNum(){
  return pageFaultNum;
}
PageTable::~PageTable(){
  delete[] this->table;
}