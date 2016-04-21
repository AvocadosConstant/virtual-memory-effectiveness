#include <stdio.h>
#include <stdlib.h>
#include <queue>

typedef struct {
    int pid;
    int reference;
    int hits;
} entry;

class TLB{
  private:
    int size;
    entry* table;
    bool full; // all refs have been hit > once

  public:
    TLB();
    ~TLB();

    int search(int pid, int reference);
    void insert(int pid, int reference);
};
