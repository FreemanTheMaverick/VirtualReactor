CXX=g++
JSON=/home/yzhangnn/nlohmann/include/

.PHONY: all

all: main Mumbler Parser Simulator
	cd src
	$(CXX) main.o Mumbler.o Parser.o Simulator.o -I$(JSON) -fopenmp -o ../VirtualReactor -Wall -O2

main: main.cpp
	cd src
	$(CXX) main.cpp -c -Wall -O2

Mumbler: Mumbler.cpp
	cd src
	$(CXX) Mumbler.cpp -c -Wall -O2 -DNDEBUG

Parser: Parser.cpp
	cd src
	$(CXX) Parser.cpp -I$(JSON) -c -Wall -O2 -DNDEBUG

Simulator: Simulator.cpp
	cd src
	$(CXX) Simulator.cpp -fopenmp -c -Wall -O2 -DNDEBUG
