#ifndef MMATH_H

#define MMATH_H
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

#endif // !MMATH_H
