#include "TLB.h"

TLB::TLB(){
  this->size = 64;
  this->table = new entry[this->size];

  for (int i = 0; i < size; ++i){
    table[i] = {-1, -1, 0};
  }
}

int TLB::search(int pid, int reference){
  for(int i = 0; i < this->size; ++i){
    if (this->table[i].pid == pid && this->table[i].reference == reference){
      this->table[i].hits++;
      return i;
    }
  }
  return -1;
}

void TLB::insert(int pid, int reference){
  if (!full){
    for(int i = 0; i < this->size; ++i){
      if (this->table[i].hits < 2){
        this->table[i].pid = pid;
        this->table[i].reference = reference;
        this->table[i].hits = 1;
        return;
      }
    }
  }
}

TLB::~TLB(){
  delete[] this->table;
}
