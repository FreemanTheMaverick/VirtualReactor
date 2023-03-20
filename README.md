# Virtual Reactor

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

## Theory
[Virtual Reactor](https://github.com/FreemanTheMaverick/VirtualReactor/) simulates concentration evolution in chemical reactions based on [Eyring equation](https://en.wikipedia.org/wiki/Eyring_equation), an equation depicting reaction rates for elementary steps:

$k=\frac{k_B T}{h}(\frac{RT}{P})^{n-1}e^{-\frac{\Delta G^\ddagger}{RT}}$

where $k$ is a one-direction (either forward or backward) elementary step rate constant, $k_B$ is the Boltzmann constant, $T$ is the temperature, $h$ is the Plank constant, $R$ is the ideal gas constant, $P$ is the pressure, $n$ is the molecularity of reactants and $\Delta G^\ddagger$ is the Gibbs free energy of activation.

The rate of change in the concentration of a chemical species, $i$, in an elementary step, $p$ is written as

$r_{ip}=m_{ip}[-k_{+,p}\displaystyle\prod_{j\in R_p}c_j^{m_{jp}}+k_{-,p}\displaystyle\prod_{j\in P_p}c_j^{m_{jp}}]$

For a chemical species in a reaction, it
