#include "PageTable.h"

PageTable::PageTable(int pid, int size){
  this->pid = pid;
  this->size = size;
  this->table = new int[size];
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

PageTable::~PageTable(){
  delete[] this->table;
}