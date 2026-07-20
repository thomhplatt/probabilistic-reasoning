#include <iostream>
#include <vector>
#include <random>

std::mt19937 gen(std::random_device{}());
std::uniform_real_distribution<float> dist(0.0, 1.0);

float random_sample(){
 return dist(gen);
}

class State{
public:
  std::string name;
  
  State(const std::string& name)
    : name(name){}
};

class MarkovChain{
public:
  std::vector<State> states;
  std::vector<std::vector<float>> matrix;  

  MarkovChain(){}

  void add_state(const State& state);
  void add_transition(const State& from, const State& to, float probability);
  void print_matrix();
  int get_state_index(const State& state);
  State predict(State current, int iterations);
};

void MarkovChain::add_state(const State& state){
  states.push_back(state);

  // add new column to the matrix
  for(auto& row : matrix){
    row.push_back(0.0f);
  }
  // add new row to the matrix
  matrix.push_back(std::vector<float>(states.size(), 0.0f));
}

void MarkovChain::add_transition(const State& from, const State& to, float probability){
  int row = get_state_index(from);
  int column = get_state_index(to);
  
  if (row == -1 || column == -1){
    std::cout << "error adding transition" << "\n";
  }
  matrix[row][column] = probability;
}

int MarkovChain::get_state_index(const State& state){
  for (int i = 0; i < states.size(); i++){
    if (states[i].name == state.name){
      return i;
    }
  }
  std::cout << "warning: " << state.name << " has not been added to the Markov Chain." << "\n";
  return -1;
}

State MarkovChain::predict(State current, int iterations){
    
  for(int i = 0; i < iterations; i++){

    int row = get_state_index(current);
    float r = random_sample();
    float cumulative = 0.0;

    std::cout << "\nStep " << i + 1 << "\n";
    std::cout << "Current state: " << current.name << "\n";
    std::cout << "Random sample: " << r << "\n";
    
    for (int column = 0; column < matrix[row].size(); column++){

      cumulative += matrix[row][column];
      
      if (r <= cumulative){
	
	std::cout << "Transition: "
		  << current.name
		  << " -> "
		  << states[column].name
		  << "\n";

	current = states[column];
	break;
      }
    }
  }
  return current;
}

void MarkovChain::print_matrix(){
  std::cout << "        ";
  for(State state: states){
     std::cout << state.name << "\t";
  }

  std::cout << "\n";

  for (int i = 0; i < states.size(); i++) {
    std::cout << states[i].name << "\t";
    for (float p : matrix[i]) {
      std::cout << p << "\t";
    }
    std::cout << "\n";
  }
}

// Main
int main(){

  // create markov chain
  MarkovChain chain;

  // create states
  State sunny("Sunny");
  State cloudy("Cloudy");
  State rainy("Rainy");

  // add states to chain
  chain.add_state(sunny);
  chain.add_state(cloudy);
  chain.add_state(rainy);

  // define transition probs
  chain.add_transition(sunny, sunny, 0.6);
  chain.add_transition(sunny, cloudy, 0.3);
  chain.add_transition(sunny, rainy, 0.1);

  chain.add_transition(cloudy, sunny, 0.2);
  chain.add_transition(cloudy, cloudy, 0.4);
  chain.add_transition(cloudy, rainy, 0.4);

  chain.add_transition(rainy, sunny, 0.1);
  chain.add_transition(rainy, cloudy, 0.4);
  chain.add_transition(rainy, rainy, 0.5);

  // display the transition matrix
  chain.print_matrix();

  // simulate iterations
  chain.predict(sunny, 15);
  
  return 0;
}

