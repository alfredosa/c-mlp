#ifndef NN_H
#define NN_H

typedef struct {
  double weight;
  double bias;
} Neuron;

typedef struct {
  Neuron **neurons;
  int num_neurons;
} Layer;

typedef struct {
  Layer **layers;
  int num_layers;
  int capacity;
} NeuralNetwork;

// Layers of NN
Layer *create_layer(int num_neurons);
int add_layer(NeuralNetwork *network, int num_neurons);
void free_layer(Layer *layer);

// Neural Network
void free_nn_all(NeuralNetwork *nn);
NeuralNetwork *create_network(int params, int outputs);
void print_nn_structure(NeuralNetwork *nn);

#endif // NN_H
