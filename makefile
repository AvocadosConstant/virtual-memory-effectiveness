all:	lab4.o lab5.o
	g++ -std=c++11	-g lab4.o -o lab4
	g++ -std=c++11	-g lab5.o -o lab5

lab4.o:	lab4.cpp
	g++ -std=c++11 -g -c lab4.cpp

lab5.o:	lab5.cpp
	g++ -std=c++11 -g -c lab5.cpp

clean:
	rm -f *.o *~ *.swp lab4 lab5

again:	clean all
