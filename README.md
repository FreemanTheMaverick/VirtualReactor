# VirtualReactor

>Simulation of concentration evolution in chemical reactions.

## Installation

+ [Virtual Reactor](https://github.com/FreemanTheMaverick/VirtualReactor/) uses [nlohmann/json](https://github.com/nlohmann/json) as the input file parser, so [nlohmann/json](https://github.com/nlohmann/json) must be installed.
+ Download and compile [Virtual Reactor](https://github.com/FreemanTheMaverick/VirtualReactor/).
```
git clone https://github.com/FreemanTheMaverick/VirtualReactor.git
cd VirtualReactor
vim makefile # Set C++ compiler and path to nlohmann/json's include.
make [-j]
```
+ Set environment variable in ```~/.bashrc```
```
alias vr=[Installation_root]/VirtualReactor/VirtualReactor
```
and
```
source ~/.bashrc
```

## Usage
```
vr test1.json
```
