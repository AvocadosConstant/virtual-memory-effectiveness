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

# Params: p=<num-processes> m=<min-address-space-size> M=<max-address-space-size> a=<page-table-size>
# Ex: make test p=5 m=1000 M=1000 a=10000
test:
	> data.txt
	for i in 0 10 20 30 40 50 60 70 80 90 99; do \
		echo "-- Repetition at $$i% --\n" >> data.txt; \
		echo "NO TLB:" >> data.txt; \
		./lab4 $(p) $(m) $(M) $(a) -r $$i; \
		./lab5 >> data.txt; \
		echo "\nW/ TLB:" >> data.txt; \
		./lab5 -t >> data.txt; \
		echo "" >> data.txt; \
	done;

clean:
	rm -f *.o *~ *.swp lab4 lab5 outputFile.txt data.txt

again:	clean all
