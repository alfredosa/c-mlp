#include "math.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double **matrix_multiplication(double **m1, double **m2, int rows1, int cols1,
                               int cols2) {
  double **m3 = malloc(rows1 * sizeof(double *));
  for (int i = 0; i < rows1; i++) {
    m3[i] = malloc(cols2 * sizeof(double));
    for (int j = 0; j < cols2; j++) {
      m3[i][j] = 0;
      for (int k = 0; k < cols1; k++) {
        m3[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
  return m3;
}

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

double random_bet_zao() { return (double)rand() / (double)RAND_MAX; }
