#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

// random number gen
std::mt19937 gen(std::random_device{}());
std::uniform_real_distribution<float> dist(0.0, 1.0);

float random_sample(){
 return dist(gen);
}

// ---------------
// classes
// ---------------

// state class
class State{
public:

  // attributes
  std::string name;

  // constructor
  State(const std::string& name)
    : name(name){}
};

// markov chain class
class MarkovChain{
public:

  // attributes
  std::vector<State> states;
  std::vector<std::vector<float>> matrix;  

  // constructor
  MarkovChain(){}

  // state functions
  void add_state(const State& state);
  void remove_state(const State& state);
  int get_state_index(const State& state);
  void print_states();

  // matrix functions
  void add_transition(const State& from, const State& to, float probability);
  void print_matrix();

  // prediction functions
  void analytic(State start, int steps);
  void matrix_mult(const std::vector<float>& state_vec, std::vector<float>& result_vec);
  void monte_carlo(State start, int steps, int simulations);
  int predict(State start, int iterations);
};

// ---------------
// MarkovChain class functions
// ---------------

// function to add a state to the markov chain (matrix)
void MarkovChain::add_state(const State& state){
  states.push_back(state);

  // add new column to the matrix
  for(auto& row : matrix){
    row.push_back(0.0f);
  }
  // add new row to the matrix
  matrix.push_back(std::vector<float>(states.size(), 0.0f));
}

// function to remove a state from the markov chain (matrix)
void MarkovChain::remove_state(const State& state){
  int index = get_state_index(state);

  if (index == -1){
    std::cout << "error removing state" << "\n";
    print_matrix();
    return;
  }

  // remove state
  states.erase(states.begin() + index);

  // remove column
  for(auto& row : matrix){
    row.erase(row.begin() + index);
  }

  // remove row
  matrix.erase(matrix.begin() + index);
  
}

// gets the index of a state in the states vector
int MarkovChain::get_state_index(const State& state){
  for (int i = 0; i < states.size(); i++){
    if (states[i].name == state.name){
      return i;
    }
  }
  std::cout << "warning: " << state.name << " not found in  Markov Chain." << "\n";
  return -1;
}

// prints the states in the states vector
void MarkovChain::print_states(){
  std::cout << "Current states: ";
  for (const State& state : states){
    std::cout <<  state.name << " ";
  }
  std::cout << "\n";
}

// function to add transition prob from state A to state B
void MarkovChain::add_transition(const State& from, const State& to, float probability){
  int row = get_state_index(from);
  int column = get_state_index(to);
  
  if (row == -1 || column == -1){
    std::cout << "error adding transition" << "\n";
  }
  matrix[row][column] = probability;
}

// prints transition matrix
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

void MarkovChain::analytic(State start, int steps){

  // define start state
  std::vector<float> state_vec(states.size(), 0);
  int current = get_state_index(start);
  state_vec[current] = 1;

  // define result state
  std::vector<float> result_vec(states.size(), 0);

  // for number of steps
  for (int i = 0; i < steps; i++){

    // preform matrix vector mult
    matrix_mult(state_vec, result_vec);

    // update state vector
    state_vec = result_vec;
  }

  std::cout << "\nAnalytic Results: \n";
  
  for (int i = 0; i < states.size(); i++){
    std::cout << std::left
	      << std::setw(8)
      	      << states[i].name
	      << result_vec[i]
	      << "\n";
  }
  
}

void MarkovChain::matrix_mult(const std::vector<float>& state_vec, std::vector<float>& result_vec){
 
 // clear result vec
  std::fill(result_vec.begin(), result_vec.end(), 0.0f);
  
  // multiple by transition matrix
  for (int row = 0; row < states.size(); row++){
    for (int col = 0; col < states.size(); col++){
      result_vec[col] += state_vec[row] * matrix[row][col];
    }
  }
}
  
void MarkovChain::monte_carlo(State start, int steps, int simulations){
  
 std::vector<int> counts(states.size(), 0);

   for (int i = 0; i < simulations; i++){
     // std::cout << "\n" <<  "simulation: " << i+1 << "\n";
     int next = predict(start, steps);
     counts[next]++;
   }

   std::cout << "\nMonte Carlo Results: \n";
   
   for (int i = 0; i < states.size(); i++){
     std::cout << std::left
	       << std::setw(8)
	       << states[i].name
	       << (float)counts[i]/simulations
	       << "\n";
   }
}

int MarkovChain::predict(State start, int steps){
  
  int current = get_state_index(start);
 
  for(int i = 0; i < steps; i++){
    int row = current;
    float r = random_sample();
    float cumulative = 0.0;

    // debugging
    // std::cout << "\nStep " << i + 1 << "\n";
    // std::cout << "Current state: " << states[current].name << "\n";
    // std::cout << "Random sample: " << r << "\n";
    
    for (int column = 0; column < matrix[row].size(); column++){
      cumulative += matrix[row][column];
      if (r <= cumulative){
	
	// debugging
	// std::cout << "Transition: "
		  // << states[current].name
		  // << " -> "
		  // << states[column].name
		  // << "\n";
	
	current = column;
	break;
      }
    }
  }
  return current;
}

// Main
int main(){

  // create markov chain
  MarkovChain weather;

  // create states
  State sunny("Sunny");
  State cloudy("Cloudy");
  State rainy("Rainy");

  // add states to chain
  weather.add_state(sunny);
  weather.add_state(cloudy);
  weather.add_state(rainy);

  // define transition probs
  weather.add_transition(sunny, sunny, 0.8);
  weather.add_transition(sunny, cloudy, 0.1);
  weather.add_transition(sunny, rainy, 0.1);

  weather.add_transition(cloudy, sunny, 0.1);
  weather.add_transition(cloudy, cloudy, 0.7);
  weather.add_transition(cloudy, rainy, 0.2);

  weather.add_transition(rainy, sunny, 0.1);
  weather.add_transition(rainy, cloudy, 0.3);
  weather.add_transition(rainy, rainy, 0.6);
  
  // display information
  std::cout << " \n ==== MARKOV CHAIN ==== \n\n";

  std::cout << "States:\n";
  
  for (int i = 0; i < weather.states.size(); i++){
    std::cout << i
	      << ". "
	      << weather.states[i].name
	      << "\n";
  }
 
  // user defines chain
  int state_index;
  int steps;
  int simulations;
  
  std::cout << "\nStarting state (0-2): ";
  std::cin >> state_index;

  if (state_index > weather.states.size() || state_index < 0){
    std::cout << "invalid selection\n";
    return 1;
  }
  
  std::cout << "Number of steps: ";
  std::cin >> steps;
  
  std::cout << "Number of simulations: ";
  std::cin >> simulations;
			    
  std::cout << "\n" << "\nTransition Matrix: \n";
  weather.print_matrix();
  
  // simulate iterations
  weather.monte_carlo(weather.states[state_index], steps, simulations);
  weather.analytic(weather.states[state_index], steps);

  return 0;
}

