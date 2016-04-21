all:	lab4.o lab5.o PageTable.o TLB.o
	g++ -std=c++11	-g lab4.o -o lab4
	g++ -std=c++11	-g PageTable.o TLB.o lab5.o -o lab5

lab4.o:	lab4.cpp
	g++ -std=c++11 -g -c lab4.cpp

lab5.o:	lab5.cpp
	g++ -std=c++11 -g -c lab5.cpp

PageTable.o:	PageTable.cpp
	g++ -std=c++11 -g -c PageTable.cpp

TLB.o:	TLB.cpp
	g++ -std=c++11 -g -c TLB.cpp

lab4: lab4.o
	g++ -std=c++11 -g -c lab4.o -o lab4

lab5: lab5.o
	g++ -std=c++11 -g -c lab5.o -o lab5

test: #takes parameters: p=<num-processes> m=<min-address-space-size> M=<max-address-space-size> p=<page-table-size>
	> data.txt
	echo "-- Repetition at 0% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 0 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 0 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 10% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 10 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 10 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 20% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 20 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 20 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 30% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 30 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 30 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 40% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 40 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 40 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 50% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 50 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 50 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 60% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 60 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 60 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 70% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 70 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 70 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 80% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 80 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 80 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 90% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 90 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 90 && ./lab5 -t >> data.txt
	echo "\n-- Repetition at 99% --\n" >> data.txt
	echo "NO TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 99 && ./lab5 >> data.txt
	echo "W/ TLB:" >> data.txt
	./lab4 $(p) $(m) $(M) $(a) -r 99 && ./lab5 -t >> data.txt

clean:
	rm -f *.o *~ *.swp lab4 lab5 outputFile.txt data.txt

again:	clean all
