#ifndef NN_H
#define NN_H

typedef struct Neuron {
  double *weights; // Array of weights
  double bias;
  int num_inputs; // Number of inputs to this neuron
} Neuron;

typedef struct Layer {
  Neuron **neurons;
  // dont think we need this... we can calc on the fly...
  int num_neurons;
  // dont think we need this... we can calc on the fly...
  int num_inputs_per_neuron;
  double *inputs;
  double *outputs;
} Layer;

typedef struct NeuralNetwork {
  double *inputs;
  // dont think we need this... we can calc on the fly...
  int num_inputs;
  Layer **layers;
  // dont think we need this... we can calc on the fly...
  int num_layers;
} NeuralNetwork;

// Neurons
Neuron *create_neuron(int num_inputs);

// Layers of NN
Layer *create_layer(int num_neurons, int params);
void free_layer(Layer *layer);

// Neural Network
void free_nn_all(NeuralNetwork *nn);
NeuralNetwork *create_network(int num_inputs, int num_outputs,
                              int num_hidden_layers, int *hidden_layer_sizes);
void print_nn_structure(NeuralNetwork *nn);

// Machine Learning babyyyyy
double forward_propagation(NeuralNetwork *nn);

#endif // NN_H
