# Markov Chain
A C++ implementation of a Markov Chain used to model probabilistic systems. 

This project compares a stochastic (Monte Carlo) sampling method with an analytical matrix-vector multiplication method. 

This model is the first in the library of probabilistic-reasoning algorithms and serves as the foundation of the Hidden-Markov Model to follow. 

## Features
- Defines states and transition probabilities as a matrix
- Simulates transitions with stochastic sampling
- Calculates exact probability with matrix-vector multiplication
- Compares stochastic and analytical results 
- Demonstrates steady-state distribution convergence

## Usage
### Running:
This program uses CMake to build depencies. Navigate to the /build directory. Use ``` make .. ``` to build and ``` ./run``` to run. 
```
~/markov_chain/build
make ..
./run
```
---
### Operation:
The program displays the states currently in the Markov Chain and prompts the user to select a starting state:

```
States:
0. Sunny
1. Cloudy
2. Rainy

Starting state (0-2):
```
The program asks for the number of steps and number of simulations:

```
Number of steps: 
Number of simulations:
```
---
### Algorithms:
#### Analytical Algorithm:
The analytical algorithm encodes the start start as a probability vector where we have 100% chance being in the start state.

```
Start state = 'sunny'
Starting Probability vector:
[1 0 0]
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
Resulting Probability vector after 1 step:
[0.8 0.1 0.1]
```
The resulting probability vector is used as the new starting vector and the process is repeated for desired number of steps. It represents the exact probability of being in each state after *n* steps.

```
Resulting Probability vector after 2 steps:
[0.66 0.18 0.16]

...

Resulting Probability after 100 steps:
[0.333334 0.388889 0.277778]
```
#### Stochastic Algorithm
The stochastic algorithm looks at the starting state and the transition matrix. It takes a random sample, and moves to a new state depending on the random sample.

For example:
```
Transition Matrix: 
        Sunny   Cloudy  Rainy
Sunny   0.8     0.1     0.1
Cloudy  0.1     0.7     0.2
Rainy   0.1     0.3     0.6

Step 1:
Starting State: 'sunny'
Random sample: 0.28
New State: 'rainy'

Step 2:
Starting State: 'sunny'
Random sample: 0.96
New State: 'rainy'

...

Step 100:
Starting State: 'rainy'
Random sample: 0.80
New State: 'cloudy'
```
After transitioning *n* steps, the algorithm records the final state. This is counted as 1 simulation. 

If the user selects 100 steps and 10,000 simulations, then the program will record the final state after 100 steps 10,000 times.

Finally, the program calculates the probabilities of each state after *n* steps and *k* simulations. 

Again, this result represents the probability of transitioning to each state after *n* steps.

```
Starting State: 'sunny'
Steps: 100
Simulations: 10,000

Results = [0.3351 0.3846 0.2803]
```
---
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




