#include "mlp/math.h"
#include "mlp/mlp.h"
#include <stdint.h>
#include <stdio.h>

int main() {

  int isloaded = load_mnist();
  if (!isloaded) {
    printf("Failed to load MNIST data\n");
  }

  NeuralNetwork *nn = create_network(784, 9); // 10 inputs, 2 outputs
  add_layer(nn, 123); // Add a hidden layer with 123 neurons
  add_layer(nn, 64);  // Add another hidden layer with 64 neurons

  print_nn_structure(nn);
  free_nn_all(nn);

  double sig = SIGMOID(1.323);
  double relu = RELU(0.56);
  double yi = TANH(0.123);
  double input[] = {1.0, 2.0, 3.0, 4.0, 1.0, 2.0, 3.0};
  double output[7];
  softmax(input, 7, output);

  print_activation_results(sig, relu, yi, output, 7);

  return 0;
}
