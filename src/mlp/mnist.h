#ifndef MNIST_H
#define MNIST_H

#define INPUT_SIZE 784 // 28x28 pixels
#define TRAIN_SIZE 60000
#define TEST_SIZE 10000
#define IMAGE_WIDTH 28
#define IMAGE_HEIGHT 28

#define MNIST_IMAGE_MAGIC 2051
#define MNIST_LABEL_MAGIC 2049
#define IMAGE_SIZE 28 * 28

// Extern declarations for the global variables
extern double train_images[TRAIN_SIZE][IMAGE_HEIGHT][IMAGE_WIDTH];
extern int train_labels[TRAIN_SIZE];
extern int num_train;

extern double test_images[TEST_SIZE][IMAGE_HEIGHT][IMAGE_WIDTH];
extern int test_labels[TEST_SIZE];
extern int num_test;

// Function prototypes
double normalize_pixel(double pixel);
int load_mnist();
int read_images(const char *filepath,
                double images[][IMAGE_HEIGHT][IMAGE_WIDTH], int max_images,
                int *num_images);
int read_labels(const char *filepath, int labels[], int max_labels,
                int *num_labels);
void print_image(double image[IMAGE_HEIGHT][IMAGE_WIDTH]);

#endif
