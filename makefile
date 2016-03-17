all:	lab4.o lab5.o PageTable.o
	g++ -std=c++11	-g lab4.o -o lab4
	g++ -std=c++11	-g PageTable.o lab5.o -o lab5

lab4.o:	lab4.cpp
	g++ -std=c++11 -g -c lab4.cpp

lab5.o:	lab5.cpp
	g++ -std=c++11 -g -c lab5.cpp

PageTable.o:	PageTable.cpp
	g++ -std=c++11 -g -c PageTable.cpp

lab4: lab4.o
	g++ -std=c++11 -g -c lab4.o -o lab4

lab5: lab5.o
	g++ -std=c++11 -g -c lab5.o -o lab5

clean:
	rm -f *.o *~ *.swp lab4 lab5 outputFile.txt

again:	clean all
