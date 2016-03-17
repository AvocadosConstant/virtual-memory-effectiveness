#include <stdio.h>
#include <stdlib.h>


class PageTable{
  private:
    int size;
    int* table;

  public:
    PageTable(int size);
    ~PageTable();

    int lookup(int reference);
};
