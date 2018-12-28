output: lab4.o
	g++ lab4.o -o lab4
lab4.o: lab4.cc
	g++ -c lab4.cc
