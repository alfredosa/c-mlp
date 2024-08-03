#include "math.h"

#include <stdio.h>
#include <string.h>

#define BAR_WIDTH 50
#define PRECISION 4

void print_ascii_bar(const char *name, double value) {
  int filled_width = (int)(value * BAR_WIDTH);
  printf("%-10s [", name);
  for (int i = 0; i < BAR_WIDTH; i++) {
    if (i < filled_width)
      printf("#");
    else
      printf(" ");
  }
  printf("] %.*f\n", PRECISION, value);
}

void print_activation_results(double sig, double relu, double yi,
                              double *softmax, int softmax_len) {
  printf("\nActivation Function Results:\n");
  printf("============================\n");
  print_ascii_bar("Sigmoid", sig);
  print_ascii_bar("ReLU", relu);
  print_ascii_bar("Tanh", yi);

  printf("\nSoftmax Results:\n");
  printf("================\n");
  char name[20];
  for (int i = 0; i < softmax_len; i++) {
    snprintf(name, sizeof(name), "Softmax[%d]", i);
    print_ascii_bar(name, softmax[i]);
  }
}

void softmax(double *input, size_t input_len, double *output) {
  double max_val = -DBL_MAX;
  double sum = 0.0;

  for (size_t i = 0; i < input_len; i++) {
    if (input[i] > max_val) {
      max_val = input[i];
    }
  }

  for (size_t i = 0; i < input_len; i++) {
    output[i] = exp(input[i] - max_val);
    sum += output[i];
  }

  for (size_t i = 0; i < input_len; i++) {
    output[i] /= sum;
  }
}