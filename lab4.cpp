#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <set>

int addUnique(std::vector<int>& vec, int elem) {
    for(const int& i : vec) {
        if(i == elem) return -1;
    }
    vec.push_back(elem);
    return 0;
}

int chooseRandomProc(std::vector<std::vector<int>>& vec, int numProcs, std::vector<int>& pageTableSizes) {
    int proc;
    for(int i = 0; i < 2 * numProcs; i++) {
        proc = std::rand() % numProcs;
        if(vec[proc].size() < pageTableSizes[proc]) return proc;
    }
    return proc;
}

int chooseRandomPage(std::vector<int>& vec, std::vector<int>& pageTableSizes) {
    int page;
    for(int i = 0; i < 100 * pageTableSizes.size(); i++) {
        bool conflict = false;
        page = (std::rand() % pageTableSizes[std::rand()%pageTableSizes.size()]) + 1;
        for(const int&j : pageTableSizes) {
            if(page == j) conflict = true;
        }
        if(conflict == false) return page;
    }
    return page;
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
        std::perror("Unexpected number of arguments.\n\t<num-processes>, <min-page-table-size>, <max-page-table-size>, and <address-space-size> must all be greater than 0.");
        exit(1);
    }
    int numProcs = atoi(argv[1]);
    int minPageTableSize = atoi(argv[2]);
    int maxPageTableSize = atoi(argv[3]);
    int addressSpaceSize = atoi(argv[4]);
    std::srand(std::time(0));

    if (numProcs <= 0 || minPageTableSize <= 0 || maxPageTableSize <= 0 || addressSpaceSize <= 0) {
        std::perror("Unexpected parameter value. <num-processes>, <min-page-table-size>, <max-page-table-size>, and <address-space-size> must all be greater than 0.");
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

    //printf("%d processes\n%d address size\n%d%% repetition\n", numProcs, addressSpaceSize, repeatPercent);

    std::vector<int> pageTableSizes(numProcs);
    //  Printing all START lines
    for(int i = 0; i < numProcs; i++) {
        int randPageTableSize = minPageTableSize + std::rand() % (maxPageTableSize + 1 - minPageTableSize);
        printf("randPageTableSize: %d\n", randPageTableSize);
        pageTableSizes[i] = randPageTableSize;
	    outputFile << "START\t" << i << "\t" << randPageTableSize << std::endl;
	}

    for(int i = 0; i < phases; i++) {
        std::vector<std::vector<int>> repetitionMatrix(numProcs);
        int repeatCount = 0;
        int accidentalRepeats = 0;
        if (i != 0) repeatPercent = (repeatPercent == 10) ? 90 : 10;

        for(int j = 0; j < numProcs * addressSpaceSize; j++) {
            int pageNum = (std::rand() % addressSpaceSize) + 1;
            int curProc = chooseRandomProc(repetitionMatrix, numProcs, pageTableSizes);
            
            //printf("j = %d\tcurProc = %d\tpageNum = %d\n", j, curProc, pageNum);

            //  if vec is empty 
            if(repetitionMatrix[curProc].size() == 0) {
                pageNum = chooseRandomPage(repetitionMatrix[curProc], pageTableSizes);
                addUnique(repetitionMatrix[curProc], pageNum) < 0;
            }
            //if random percent isn't within specified percent
            else if(std::rand() % 100 >= repeatPercent) {
                pageNum = chooseRandomPage(repetitionMatrix[curProc], pageTableSizes);
                if(addUnique(repetitionMatrix[curProc], pageNum) < 0) {
                    printf("Accidentally chose page %d\n",pageNum);
                    accidentalRepeats++;
                }
            }
            else {
                // Repeat a pagenum from list
                pageNum = repetitionMatrix[curProc][std::rand() % repetitionMatrix[curProc].size()];
                repeatCount++;
            }
    	    outputFile << "REFERENCE\t" << curProc << "\t" << pageNum << std::endl;
           // printf("REFERENCE\t%d\t%d\n", curProc, pageNum);
        }
        printMatrix(repetitionMatrix);
        printf("\tRepeated %d times out of %d. That's %2.2f%%! Specified percentage is %d%%.\n\n", repeatCount + accidentalRepeats, numProcs*addressSpaceSize, 100.0 * (repeatCount + accidentalRepeats)/(numProcs*addressSpaceSize), repeatPercent);
        printf("\tRepeated %d times on purpose and %d times by accident\n\n.", repeatCount, accidentalRepeats);
    }
    //  Printing all START lines
    for(int i = 0; i < numProcs; i++) {
        outputFile << "TERMINATE\t" << i << std::endl;
    }
}
