
main: MaxThroughput.o
	g++ MaxThroughput.o main.cpp -o main

MaxThroughput.o: MaxThroughput.cpp MaxThroughput.h
	g++ -c MaxThroughput.cpp -o MaxThroughput.o