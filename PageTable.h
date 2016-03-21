#include <stdio.h>
#include <stdlib.h>


class PageTable{
  private:
    int pid;
    int size;
    int pageFaultNum;
    int* table;

  public:
    PageTable(int pid, int size);
    ~PageTable();

    int lookup(int reference);
    int getPid();
    int isSpace();
    void add(int vpn);
    void addPageFault();
    int getPageFaultNum();
};
