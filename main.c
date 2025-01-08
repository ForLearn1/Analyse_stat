#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// Use the RAND_MAX constant defined by the standard library
#undef RAND_MAX
#define RAND_MAX 32767

double uniform_distribution() {
    return (double)rand() / (RAND_MAX + 1.0);
}

void box_muller_x1_x2(double u1, double u2, double *x1, double *x2) {
    *x1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    *x2 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
}

double generate_normal_error(double mu, double sigma) {
    double u1, u2;
    do {
        u1 = uniform_distribution();
        u2 = uniform_distribution();
    } while (u1 <= 0.0); // ensure u1 is strictly positive to avoid log(0)

    double x1, x2;
    box_muller_x1_x2(u1, u2, &x1, &x2);
    return mu + sigma * x1;
}

int main() {
    // Initialize the random number generator
    srand((unsigned int)time(NULL));

    // Sample size
    const int sample_size = 1000000;
    double *sample = (double *)malloc(sample_size * sizeof(double));
    if (sample == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Measure the start time
    clock_t start_time = clock();

    // Generate sample values
    for (int i = 0; i < sample_size; i++) {
        sample[i] = generate_normal_error(0, pow(2, -3.19));
    }

    // Measure the end time and calculate the elapsed time
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Display the first sample values horizontally
    printf("First sample values:\n");
    for (int i = 0; i < 100; i++) {
        printf("%f ", sample[i]);
    }
    printf("\n");

    // Display the time taken to generate the sample values
    printf("Time taken to generate sample values: %f seconds\n", time_taken);

    // Write values to a CSV file
    FILE *file = fopen("sample_data.csv", "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        free(sample);
        return 1;
    }

    for (int i = 0; i < sample_size; i++) {
        fprintf(file, "%f\n", sample[i]);
    }
    fclose(file);

    // Calculate and display some descriptive statistics
    double sum = 0.0;
    double sum_sq = 0.0;
    for (int i = 0; i < sample_size; i++) {
        sum += sample[i];
        sum_sq += sample[i] * sample[i];
    }
    double mean = sum / sample_size;
    double variance = (sum_sq / sample_size) - (mean * mean);

    printf("\nDescriptive statistics of the sample:\n");
    printf("Mean: %f\n", mean);
    printf("Variance: %f\n", variance);

    // Free the allocated memory
    free(sample);

    return 0;
}
