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
vr input.json > output.txt
```

## Version history

### v1.1
1. Concentrations and rates of one step are consistent now. In v1.0, the rates were actually of last step.
2. The zeroth step is now the initial state of a reaction. In v1.0, the zeroth step was actually the moment right after the initial state.
3. ```ignore_comments``` toggled to ```true``` in ```nlohmann/json```'s ```parse``` function, so comments with ```//``` and ```/* */``` in input file to Virtual Reactor are permitted. In v1.0, any comment in input file caused errors.
4. The two examples are replaced by new ones in ```/example```.
5. Source codes are moved to ```/src```.
None of the changes above causes non-negligible differences between results given by v1.0 and v1.1.

### v1.0
Initial version.

## Theory
[Virtual Reactor](https://github.com/FreemanTheMaverick/VirtualReactor/) simulates concentration evolution in chemical reactions based on [Eyring equation](https://en.wikipedia.org/wiki/Eyring_equation), an equation depicting reaction rates for elementary steps:

$k=\displaystyle\frac{k_\mathrm{B} T}{h}(\displaystyle\frac{RT}{P})^{n-1}e^{-\frac{\Delta G^\ddagger}{RT}}$

where $k$ is a one-direction (either forward or backward) elementary step rate constant, $k_\mathrm{B}$ is the Boltzmann constant, $T$ is the temperature, $h$ is the Plank constant, $R$ is the ideal gas constant, $P$ is the pressure, $n$ is the molecularity of reactants and $\Delta G^\ddagger$ is the Gibbs free energy of activation.

The rate of change in the concentration of a chemical species, $i$, in an elementary step, $p$, is written as

$r_{ip}=\pm m_{ip}[-k_{+,p}\displaystyle\prod_{j\in R_p}c_j^{m_{jp}}+k_{-,p}\displaystyle\prod_{j\in P_p}c_j^{m_{jp}}]$

where $m_{ip}$ is the molecularity of species $i$ in step $p$, $k_{\pm,p}$ is the rate constant of the forward/backward reaction of step $p$, $R_p/P_p$ is the set of reactants/products involved in step $p$ and $c_j$ is the instant concentration of species $j$. The $\pm$ sign depends on whether $i$ is a reactant or a product of $p$. The total rate of change in the concentration of $i$ is thus

$\displaystyle\frac{\mathrm{d} c_i}{\mathrm{d} t}=r_i=\displaystyle\sum_{p\in S}r_{ip}$

where $S$ is the set of elementary steps.

[Virtual Reactor](https://github.com/FreemanTheMaverick/VirtualReactor/) computes all rates of change in concentrations given the information of species and transition states of a reaction system at a moment and update the concentrations for the next moment with Euler method:

$c_i(t+\Delta t)=c_i(t)+\displaystyle\frac{\mathrm{d} c_i}{\mathrm{d} t}\Delta t$

where $\Delta t$ is the user-defined time step for simulation.
