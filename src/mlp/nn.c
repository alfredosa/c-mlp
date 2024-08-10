#include "nn.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

Neuron *create_neuron(int num_inputs) {
  Neuron *neuron = malloc(sizeof(Neuron));
  if (neuron == NULL)
    return NULL;

  neuron->weights = malloc(sizeof(double) * num_inputs);
  if (neuron->weights == NULL) {
    free(neuron);
    return NULL;
  }

  for (int i = 0; i < num_inputs; i++) {
    neuron->weights[i] = random_bet_zao();
  }
  neuron->bias = random_bet_zao();
  neuron->num_inputs = num_inputs;
  return neuron;
}

Layer *create_layer(int num_neurons, int params) {
  Layer *layer = malloc(sizeof(Layer));
  if (layer == NULL)
    return NULL;

  layer->neurons = malloc(sizeof(Neuron *) * num_neurons);
  if (layer->neurons == NULL) {
    free(layer);
    return NULL;
  }

  for (int i = 0; i < num_neurons; i++) {
    layer->neurons[i] = create_neuron(params);
    if (layer->neurons[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(layer->neurons[j]->weights);
        free(layer->neurons[j]);
      }
      free(layer->neurons);
      free(layer);
      return NULL;
    }
  }

  layer->num_neurons = num_neurons;
  layer->num_inputs_per_neuron = params;
  layer->inputs = malloc(sizeof(double) * params);
  layer->outputs = malloc(sizeof(double) * num_neurons);

  if (layer->inputs == NULL || layer->outputs == NULL) {
    for (int i = 0; i < num_neurons; i++) {
      free(layer->neurons[i]->weights);
      free(layer->neurons[i]);
    }
    free(layer->neurons);
    free(layer->inputs);
    free(layer->outputs);
    free(layer);
    return NULL;
  }

  return layer;
}

/* NeuralNetwork creates an NN with inputs and outputs but its flexible enough
to allow the user to add hidden layers at ease. simpy:

NeuralNetwork *nn = create_network(10, 2);  // 10 inputs, 2 outputs
add_layer(nn, 123);  // Add a hidden layer with 123 neurons
add_layer(nn, 64);   // Add another hidden layer with 64 neurons

this is beautiful. Dont forget to destroy. A lot of mem allocs.
*/
NeuralNetwork *create_network(int num_inputs, int num_outputs,
                              int num_hidden_layers, int *hidden_layer_sizes) {
  NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));
  if (nn == NULL)
    return NULL;

  nn->num_layers = num_hidden_layers + 1;
  nn->num_inputs = num_inputs;
  nn->inputs = malloc(sizeof(double) * num_inputs);
  nn->layers = malloc(sizeof(Layer *) * nn->num_layers);

  if (nn->inputs == NULL || nn->layers == NULL) {
    free(nn->inputs);
    free(nn->layers);
    free(nn);
    return NULL;
  }

  int prev_layer_size = num_inputs;
  for (int i = 0; i < num_hidden_layers; i++) {
    nn->layers[i] = create_layer(hidden_layer_sizes[i], prev_layer_size);
    if (nn->layers[i] == NULL) {
      // Free previously allocated layers
      for (int j = 0; j < i; j++) {
        free_layer(nn->layers[j]);
      }
      free(nn->inputs);
      free(nn->layers);
      free(nn);
      return NULL;
    }
    prev_layer_size = hidden_layer_sizes[i];
  }

  // Create output layer
  nn->layers[nn->num_layers - 1] = create_layer(num_outputs, prev_layer_size);
  if (nn->layers[nn->num_layers - 1] == NULL) {
    // Free all allocated layers
    for (int i = 0; i < num_hidden_layers; i++) {
      free_layer(nn->layers[i]);
    }
    free(nn->inputs);
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
      if (layer->neurons[i] != NULL) {
        // Free the weights of each neuron
        free(layer->neurons[i]->weights);
        // Free the neuron itself
        free(layer->neurons[i]);
      }
    }
    // Free the array of neuron pointers
    free(layer->neurons);
  }

  // Free the input and output arrays
  free(layer->inputs);
  free(layer->outputs);

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
  printf("| Total layers: %d, Total Parameters: %d\n", nn->num_layers,
         nn->num_inputs);
  for (int i = 0; i < nn->num_layers; i++) {
    if (nn->layers[i] == NULL) {
      printf("Error: Layer %d is NULL\n", i);
      return;
    }
    if (i == nn->num_layers - 1) {
      printf("| Output Layer: %d neurons\n", nn->layers[i]->num_neurons);
    } else
      printf("| Hidden Layer %d: %d neurons\n", i + 1,
             nn->layers[i]->num_neurons);
  }

  printf("|..........................................................\n");
}