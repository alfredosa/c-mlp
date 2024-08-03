#include "mnist.h"
#include <stdio.h>
#include <stdlib.h>

// Modified variable declarations
double train_images[TRAIN_SIZE][IMAGE_HEIGHT][IMAGE_WIDTH];
int train_labels[TRAIN_SIZE];
int num_train;

double test_images[TEST_SIZE][IMAGE_HEIGHT][IMAGE_WIDTH];
int test_labels[TEST_SIZE];
int num_test;

// Function to swap endianness
uint32_t swap_endian(uint32_t val) {
  return ((val << 24) & 0xff000000) | ((val << 8) & 0x00ff0000) |
         ((val >> 8) & 0x0000ff00) | ((val >> 24) & 0x000000ff);
}

// Function to read images
int read_images(const char *filepath,
                double images[][IMAGE_HEIGHT][IMAGE_WIDTH], int max_images,
                int *num_images) {
  FILE *file = fopen(filepath, "rb");
  if (!file) {
    printf("Cannot open file %s\n", filepath);
    return 0;
  }

  uint32_t magic, size, rows, cols;
  fread(&magic, sizeof(uint32_t), 1, file);
  fread(&size, sizeof(uint32_t), 1, file);
  fread(&rows, sizeof(uint32_t), 1, file);
  fread(&cols, sizeof(uint32_t), 1, file);

  magic = swap_endian(magic);
  size = swap_endian(size);
  rows = swap_endian(rows);
  cols = swap_endian(cols);

  if (magic != MNIST_IMAGE_MAGIC) {
    printf("Invalid magic number in image file: %d\n", magic);
    fclose(file);
    return 0;
  }

  *num_images = size > max_images ? max_images : size;

  for (int i = 0; i < *num_images; i++) {
    unsigned char buffer[IMAGE_HEIGHT * IMAGE_WIDTH];
    fread(buffer, 1, IMAGE_HEIGHT * IMAGE_WIDTH, file);
    for (int r = 0; r < IMAGE_HEIGHT; r++) {
      for (int c = 0; c < IMAGE_WIDTH; c++) {
        // hehehe irc
        images[i][r][c] = buffer[r * IMAGE_WIDTH + c] / 255.0;
      }
    }
  }

  fclose(file);
  return 1;
}

// Function to read labels
int read_labels(const char *filepath, int labels[], int max_labels,
                int *num_labels) {
  FILE *file = fopen(filepath, "rb");
  if (!file) {
    printf("Cannot open file %s\n", filepath);
    return 0;
  }

  uint32_t magic, size;
  fread(&magic, sizeof(uint32_t), 1, file);
  fread(&size, sizeof(uint32_t), 1, file);
  magic = swap_endian(magic);
  size = swap_endian(size);

  if (magic != MNIST_LABEL_MAGIC) {
    printf("Invalid magic number in label file: %d\n", magic);
    fclose(file);
    return 0;
  }

  *num_labels = size > max_labels ? max_labels : size;

  unsigned char buffer[*num_labels];
  fread(buffer, 1, *num_labels, file);
  for (int i = 0; i < *num_labels; i++) {
    labels[i] = buffer[i];
  }

  fclose(file);
  return 1;
}

// Main function to load MNIST data
int load_mnist() {
  const char *train_images_file = "dataset/train-images.idx3-ubyte";
  const char *train_labels_file = "dataset/train-labels.idx1-ubyte";
  const char *test_images_file = "dataset/t10k-images.idx3-ubyte";
  const char *test_labels_file = "dataset/t10k-labels.idx1-ubyte";

  // LOAD TRAIN IMAGES AND LABELS
  if (!read_images(train_images_file, train_images, TRAIN_SIZE, &num_train)) {
    return 0;
  }
  if (!read_labels(train_labels_file, train_labels, TRAIN_SIZE, &num_train)) {
    return 0;
  }

  // LOAD TEST IMAGES AND LABELS
  if (!read_images(test_images_file, test_images, TEST_SIZE, &num_test)) {
    return 0;
  }
  if (!read_labels(test_labels_file, test_labels, TEST_SIZE, &num_test)) {
    return 0;
  }

  return 1;
}

// Function to print an image (for debugging)
void print_image(double image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
  for (int i = 0; i < IMAGE_HEIGHT; i++) {
    printf("             ");
    for (int j = 0; j < IMAGE_WIDTH; j++) {
      if (image[i][j] < 0.1)
        printf(" ");
      else if (image[i][j] < 0.3)
        printf(".");
      else if (image[i][j] < 0.5)
        printf("*");
      else if (image[i][j] < 0.8)
        printf("-");
      else
        printf("#");
    }
    printf("\n");
  }
}
