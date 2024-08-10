#include "mlp/math.h"
#include "mlp/mlp.h"
#include <stdint.h>
#include <stdio.h>

#define H_LAYERS 2

int main() {

  int isloaded = load_mnist();
  if (!isloaded) {
    printf("Failed to load MNIST data\n");
  }

  int layerparams[H_LAYERS] = {86, 64};
  NeuralNetwork *nn =
      create_network(784, 9, H_LAYERS, layerparams); // 10 inputs, 2 outputs

  print_nn_structure(nn);
  free_nn_all(nn);

  return 0;
}
