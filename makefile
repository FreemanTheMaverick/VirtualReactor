CXX=g++
JSON=/path/to/nlohmann/include/

.PHONY: all

all: main Mumbler Parser Simulator
	$(CXX) src/main.o src/Mumbler.o src/Parser.o src/Simulator.o -I$(JSON) -o VirtualReactor -Wall -O2
	rm src/*.o

main: src/main.cpp
	$(CXX) src/main.cpp -c -o src/main.o -Wall -O2

Mumbler: src/Mumbler.cpp
	$(CXX) src/Mumbler.cpp -c -o src/Mumbler.o -Wall -O2 -DNDEBUG

Parser: src/Parser.cpp
	$(CXX) src/Parser.cpp -I$(JSON) -c -o src/Parser.o -Wall -O2 -DNDEBUG

Simulator: src/Simulator.cpp
	$(CXX) src/Simulator.cpp -c -o src/Simulator.o -Wall -O2 -DNDEBUG
