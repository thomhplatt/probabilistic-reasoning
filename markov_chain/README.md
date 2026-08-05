# Markov Chain
A C++ implementation of a Markov Chain used to model probabilistic systems. 

This project compares a stochastic (Monte Carlo) sampling method with an analytical matrix-vector multiplication method. 

This model is the first in the library of probabilistic-reasoning algorithms and serves as the foundation of the Hidden-Markov Model to follow. 

## Features
- Define states with transition probabilities
- Simulate transitions with stochastic (Monte Carlo) sampling
- Calculate exact probability with matrix-vector multiplication
- Compare simulated and analytical results 
- Demonstrate steady-state distribution convergence

## Usage
```
~/markov_chain/build
make
./run
```
### Program:
The program displays the states currently in the Markov Chain and prompts the user to select a starting state:

```
States:
0. Sunny
1. Cloudy
2. Rainy

Starting state (0-2):
```
The program will then ask for the number of steps and number of simulations:

```
Number of steps: 
Number of simulations:
```
The program will then run the following algorithms.

#### Analytical Algorithm:
The analytical algorithm encodes the start start as a probability vector where we have 100% chance being in the start state.

```
Starting Probability: 
start state = 'sunny'
[ 1 0 0 ]
```

The algorithm then multiplies this vector by the transition matrix. 

```
Transition Matrix: 
        Sunny   Cloudy  Rainy
Sunny   0.8     0.1     0.1
Cloudy  0.1     0.7     0.2
Rainy   0.1     0.3     0.6
```
The resulting probability vector is calculated.

```
Resulting Probability:
[0.8 0.1 0.1]
```
The resulting probability vector is used as the new starting vector and the process is repeated for desired number of steps.

#### Stochastic Algorithm





### Full Example Output
```
 ==== MARKOV CHAIN ==== 

States:
0. Sunny
1. Cloudy
2. Rainy

Starting state (0-2): 0
Number of steps: 25
Number of simulations: 1000


Transition Matrix: 
        Sunny   Cloudy  Rainy
Sunny   0.8     0.1     0.1
Cloudy  0.1     0.7     0.2
Rainy   0.1     0.3     0.6

Monte Carlo Results: 
Sunny   0.346
Cloudy  0.384
Rainy   0.27

Analytic Results: 
Sunny   0.333423
Cloudy  0.388829
Rainy   0.277748
```
## Results


## Applied Skills
- Modern C++
- Object-Oriented Programming
- Probability and Statistics
- Linear algebra
- Numerical Simulation
- CMake
  
## Usage




