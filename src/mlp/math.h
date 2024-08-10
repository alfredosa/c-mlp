#ifndef MMATH_H
#define MMATH_H

#include "nn.h"
#define BAR_WIDTH 50
#define PRECISION 6

#include <float.h>
#include <math.h>
#include <stddef.h>

#define SIGMOID(x) (1 / (1 + exp(-x)))
#define RELU(x) ((x) > 0 ? (x) : 0)
#define TANH(x) (exp(x) - exp(-x)) / (exp(x) + exp(-x))
#define LIN(x) (x)

#include <float.h>
#include <math.h>

void print_ascii_bar(const char *name, double value);
void print_activation_results(double sig, double relu, double yi,
                              double *softmax, int softmax_len);

void softmax(double *input, size_t input_len, double *output);

/* ZAO means Zero And ONE :) but sounds cooler.
    Someone random bet on ZAO please. */
double random_bet_zao();

double **matrix_multiplication(double **m1, double **m2, int rows1, int cols1,
                               int cols2);

#endif // !MMATH_H
