#include <stdio.h>
#include <stdlib.h>


class PageTable{
  private:
    int pid;
    int size;
    int* table;

  public:
    PageTable(int pid, int size);
    ~PageTable();

    int lookup(int reference);
    int getPid();
};
