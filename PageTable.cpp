#include "PageTable.h"

PageTable::PageTable(int pid, int size){
  this->pid = pid;
  this->size = size;
  this->table = new int[size];

  for (int i = 0; i < size; ++i)
  {
    table[i] = 0;
    fifo.push(i);
  }
}

int PageTable::lookup(int reference){
  for(int i = 0; i < this->size; ++i){
    if(this->table[i] == reference){
      return i;
    }
  }
  return -1;
}

int PageTable::getPid(){
  return this->pid;
}

int PageTable::replace(int vpn){
  int popped = this->fifo.front();
  this->fifo.pop();
  table[popped] = vpn;
  this->fifo.push(popped);
  return popped;
}

PageTable::~PageTable(){
  delete[] this->table;
}
