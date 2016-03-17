#include "PageTable.h"

PageTable::PageTable(int size){
  this->size = size;
  this->table = new int[size];
}

PageTable::lookup(int reference){
  for(int i = 0; i < this->size; ++i){
    if(this->table[i] == reference){
      return 1;
    }
  }
  return 0;
}

PageTable::~PageTable(){
  delete[] this->table;
}