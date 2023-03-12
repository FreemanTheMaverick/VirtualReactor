CXX=g++
JSON=/path/to/nlohmann/include

.PHONY: all

all: main Mumbler Parser Simulator
	$(CXX) main.o Mumbler.o Parser.o Simulator.o -I$(JSON) -fopenmp -o VirtualReactor -Wall -O2

main: main.cpp
	$(CXX) main.cpp -c -Wall -O2

Mumbler: Mumbler.cpp
	$(CXX) Mumbler.cpp -c -Wall -O2 -DNDEBUG

Parser: Parser.cpp
	$(CXX) Parser.cpp -I$(JSON) -c -Wall -O2 -DNDEBUG

Parser_debug: Parser.cpp
	$(CXX) Parser.cpp -I$(JSON) -Wall -O2

Simulator: Simulator.cpp
	$(CXX) Simulator.cpp -fopenmp -c -Wall -O2 -DNDEBUG
