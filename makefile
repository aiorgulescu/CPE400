INC = include/
SRC = src/
BUILD = build/
CFLAGS = -std=c++17 -Wall

main: maxthroughput.o
	g++ $(CFLAGS) $(BUILD)maxthroughput.o $(SRC)main.cpp -o bin/main

maxthroughput.o: $(SRC)MaxThroughput.cpp $(INC)MaxThroughput.hpp $(INC)Node.hpp
	g++ $(CFLAGS) -c $(SRC)MaxThroughput.cpp -o $(BUILD)maxthroughput.o

clean:
	rm ./build/*.o
	rm ./bin/main