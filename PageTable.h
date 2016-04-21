#include <stdio.h>
#include <stdlib.h>
#include <queue>

class PageTable{
  private:
    int pid;
    int size;
    int pageFaultNum;
    int* table;
    std::queue<int> fifo;

  public:
    PageTable(int pid, int size);
    ~PageTable();

    int lookup(int reference);
    int getPid();
    int replace(int vpn);
    int getPageFaultNum();
};
