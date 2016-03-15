#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <set>

void addUnique(std::vector<int>& vec, int elem) {
    for(const int& i : vec) {
        if(i == elem) return;
    }
    vec.push_back(elem);
}

void printMatrix(std::vector<std::vector<int>>& vec) {
    for(int i = 0; i < vec.size(); i++) {
        printf("Process %d called pages {", i);
        for(int j = 0; j < vec[i].size(); j++) {
            if(j == vec[i].size() - 1) printf("%d", vec[i][j]);
            else printf("%d, ", vec[i][j]);
        }
        printf("}\n");
    }
}

int main(int argc, char* argv[]){
    if(argc != 4) {
        std::perror("Unexpected number of arguments!");
        return 0;
    }
    int numProcs = atoi(argv[1]);
    int addressSize = atoi(argv[2]);
    int repeatPercent = atoi(argv[3]);

    //printf("%d processes\n%d address size\n%d%% repetition\n", numProcs, addressSize, repeatPercent);
    
    //  Printing all START lines
    for(int i = 0; i < numProcs; i++) printf("START\t%d\t%d\n", i, addressSize);

    std::vector<std::vector<int>> repetitionMatrix(numProcs);

    int repeatCount = 0;
    for(int i = 0; i < numProcs * addressSize; i++) {
        int curProc = std::rand() % numProcs;
        int pageNum = std::rand() % addressSize; 
        //printf("i = %d\tcurProc = %d\tpageNum = %d\n", i, curProc, pageNum);
        
        //  if vec is empty OR if random percent isn't within specified percent
        if(repetitionMatrix[curProc].size() == 0 || std::rand() % 100 >= repeatPercent ) {
            addUnique(repetitionMatrix[curProc], pageNum);
        }
        else {
            // Repeat a pagenum from list
            pageNum = repetitionMatrix[curProc][std::rand() % repetitionMatrix[curProc].size()];
            repeatCount++;
        }
        printf("REFERENCE\t%d\t%d\n", curProc, pageNum); 
    }

    //  Printing all START lines
    for(int i = 0; i < numProcs; i++) printf("TERMINATE\t%d\n", i);


    //printMatrix(repetitionMatrix);
    //printf("\tRepeated %d times out of %d. That's %f%%! Specified percentage is %d%%.\n\n", repeatCount, numProcs*addressSize, 1.0 * repeatCount/(numProcs*addressSize), repeatPercent);
}
