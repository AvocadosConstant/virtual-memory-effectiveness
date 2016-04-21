#include "PageTable.h"

PageTable::PageTable(int pid, int size){
  this->pid = pid;
  this->size = size;
  this->table = new int[size];
  this->pageFaultNum = 0;

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
  this->pageFaultNum++;

  int popped = this->fifo.front();
  this->fifo.pop();
  table[popped] = vpn;
  this->fifo.push(popped);
  return popped;
}

int PageTable::getPageFaultNum(){
  return this->pageFaultNum;
}

PageTable::~PageTable(){
  delete[] this->table;
}
