#include "nn.h"
#include <stdio.h>
#include <stdlib.h>

Layer *create_layer(int num_neurons) {
  Layer *layer = malloc(sizeof(Layer));
  layer->neurons = malloc(sizeof(Neuron *) * num_neurons);
  layer->num_neurons = num_neurons;

  for (int i = 0; i < num_neurons; i++) {
    Neuron *neuron = malloc(sizeof(Neuron));
    neuron->weight = 0.2f;
    neuron->bias = 0.5f;
    layer->neurons[i] = neuron;
  }

  return layer;
}

int add_layer(NeuralNetwork *nn, int num_neurons) {
  if (nn == NULL || nn->num_layers < 2) {
    return 0; // Invalid network
  }

  // Create the new layer
  Layer *new_layer = create_layer(num_neurons);
  if (new_layer == NULL)
    return 0; // Failed to create layer

  // Increase the size of the layers array
  Layer **new_layers =
      realloc(nn->layers, sizeof(Layer *) * (nn->num_layers + 1));
  if (new_layers == NULL) {
    free_layer(new_layer);
    return 0; // Failed to reallocate
  }
  nn->layers = new_layers;

  // Move the output layer
  nn->layers[nn->num_layers] = nn->layers[nn->num_layers - 1];
  // Insert the new layer before the output layer
  nn->layers[nn->num_layers - 1] = new_layer;
  nn->num_layers++;

  return 1; // Success
}

/* NeuralNetwork creates an NN with inputs and outputs but its flexible enough
to allow the user to add hidden layers at ease. simpy:

NeuralNetwork *nn = create_network(10, 2);  // 10 inputs, 2 outputs
add_layer(nn, 123);  // Add a hidden layer with 123 neurons
add_layer(nn, 64);   // Add another hidden layer with 64 neurons

this is beautiful. Dont forget to destroy. A lot of mem allocs.
*/
NeuralNetwork *create_network(int inputs, int outputs) {
  NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));
  if (nn == NULL)
    return NULL;

  // Start with 2 layers (input and output)
  int initial_layers = 2;
  nn->layers = malloc(sizeof(Layer *) * initial_layers);
  if (nn->layers == NULL) {
    free(nn);
    return NULL;
  }

  nn->num_layers = initial_layers;
  nn->capacity = initial_layers;

  nn->layers[0] = create_layer(inputs);

  nn->layers[1] = create_layer(outputs);

  if (nn->layers[0] == NULL || nn->layers[1] == NULL) {
    if (nn->layers[0])
      free_layer(nn->layers[0]);
    if (nn->layers[1])
      free_layer(nn->layers[1]);
    free(nn->layers);
    free(nn);
    return NULL;
  }

  return nn;
}

void free_nn_all(NeuralNetwork *nn) {
  if (nn == NULL) {
    return;
  }

  // Free each layer
  for (int i = 0; i < nn->num_layers; i++) {
    if (nn->layers[i] != NULL) {
      free_layer(nn->layers[i]);
    }
  }
  free(nn->layers);
  free(nn);
}

void free_layer(Layer *layer) {
  if (layer == NULL) {
    return;
  }

  // Free each neuron in the layer
  if (layer->neurons != NULL) {
    for (int i = 0; i < layer->num_neurons; i++) {
      free(layer->neurons[i]);
    }
    // Free the array of neuron pointers
    free(layer->neurons);
  }

  // Free the layer structure itself
  free(layer);
}

void print_nn_structure(NeuralNetwork *nn) {
  printf("|..........................................................\n");

  if (nn == NULL) {
    printf("Error: Neural Network is NULL\n");
    return;
  }

  printf("| Neural Network Structure:\n");
  printf("| Total layers: %d\n", nn->num_layers);

  for (int i = 0; i < nn->num_layers; i++) {
    if (nn->layers[i] == NULL) {
      printf("Error: Layer %d is NULL\n", i);
      return;
    }
    printf("| Layer %d: %d neurons\n", i, nn->layers[i]->num_neurons);
  }

  printf("|..........................................................\n");
}