#include "mlp/mlp.h"
#include <stdint.h>
#include <stdio.h>

int main() {

  int isloaded = load_mnist();
  if (!isloaded) {
    printf("Failed to load MNIST data\n");
  }

  NeuralNetwork *nn = create_network(10, 2); // 10 inputs, 2 outputs
  add_layer(nn, 123); // Add a hidden layer with 123 neurons
  add_layer(nn, 82);  // Add a hidden layer with 123 neurons
  add_layer(nn, 64);  // Add another hidden layer with 64 neurons

  print_nn_structure(nn);
  free_nn_all(nn);

  return 0;
}
