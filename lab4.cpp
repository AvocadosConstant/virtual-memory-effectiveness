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
    if(argc != 7) {
        std::perror("Unexpected number of arguments.");
        exit(1);
    }
    int numProcs = atoi(argv[1]);
    int minAddressSize = atoi(argv[2]);
    int maxAddressSize = atoi(argv[3]);
    int tableSize = atoi(argv[4]);

    if (numProcs <= 0 || minAddressSize <= 0 || maxAddressSize <= 0 || tableSize <= 0) {
        std::perror("Unexpected parameter value. <num-processes>, <min-address-space-size>, <max-address-space-size>, and <page-table-size> must all be greater than 0.");
        exit(1);
    }

    int repeatPercent, phases;
    if (argv[5][1] == 'p') {
        repeatPercent = 10;
        phases = atoi(argv[6]);
    }else if (argv[5][1] == 'r') {
        if (atoi(argv[6]) < 0 || atoi(argv[6]) >= 100){
            std::perror("Unexpected value for <repetition-percentage>. Must be in the range [0,100).");
            exit(1);
        }else{
            repeatPercent = atoi(argv[6]);
            phases = 1;
        }
    }else{
        std::perror("Unexpected argument for <repetition-flag>. Must be \"-p\" or \"-r\".");
        exit(1);
    }

    /* open file in write mode */
    std::ofstream outputFile;
    outputFile.open("outputFile.txt");

    //printf("%d processes\n%d address size\n%d%% repetition\n", numProcs, tableSize, repeatPercent);

    //  Printing all START lines
    for(int i = 0; i < numProcs; i++) {
        int randAddressSize = minAddressSize + std::rand() % (maxAddressSize + 1 - minAddressSize);
	    outputFile << "START\t" << i << "\t" << randAddressSize << std::endl;
	}

    for(int i = 0; i < phases; i++) {
        std::vector<std::vector<int>> repetitionMatrix(numProcs);
        int repeatCount = 0;
        if (i != 0) repeatPercent = (repeatPercent == 10) ? 90 : 10;

        for(int j = 0; j < numProcs * tableSize; j++) {
            int curProc = std::rand() % numProcs;
            int pageNum = std::rand() % tableSize;
            //printf("j = %d\tcurProc = %d\tpageNum = %d\n", j, curProc, pageNum);

            //  if vec is empty OR if random percent isn't within specified percent
            if(repetitionMatrix[curProc].size() == 0 || std::rand() % 100 >= repeatPercent ) {
                addUnique(repetitionMatrix[curProc], pageNum);
            }
            else {
                // Repeat a pagenum from list
                pageNum = repetitionMatrix[curProc][std::rand() % repetitionMatrix[curProc].size()];
                repeatCount++;
            }
    	    outputFile << "REFERENCE\t" << curProc << "\t" << pageNum << std::endl;
            //printf("REFERENCE\t%d\t%d\n", curProc, pageNum);
        }
        //printMatrix(repetitionMatrix);
        //printf("\tRepeated %d times out of %d. That's %f%%! Specified percentage is %d%%.\n\n", repeatCount, numProcs*tableSize, 1.0 * repeatCount/(numProcs*tableSize), repeatPercent);
    }
    //  Printing all START lines
    for(int i = 0; i < numProcs; i++) {
        outputFile << "TERMINATE\t" << i << std::endl;
    }
}
