#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

int main(int argc, char* argv[]){
    if(argc != 4) {
        std::perror("Unexpected number of arguments!");
        return 0;
    }
    int numProcs = atoi(argv[1]);
    int addressSize = atoi(argv[2]);
    int repeatPercent = atoi(argv[3]);

    printf("%d processes\n%d address size\n%d\% repetition\n", numProcs, addressSize, repeatPercent);
    return 0;
}
