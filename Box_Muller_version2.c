#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Structure pour contenir les deux résultats de Box-Muller
typedef struct {
  double x1;
  double x2;
} BoxMullerResult;

double randomize() {
  return (double)rand() / (RAND_MAX + 1.0);
}

BoxMullerResult box_muller_x1_x2(double u1, double u2) {
  BoxMullerResult result;
  result.x1 = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
  result.x2 = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
  return result;
}

double generate_normal_error(double mu, double sigma) {
  double u1 = randomize();
  double u2 = randomize();
  BoxMullerResult result = box_muller_x1_x2(u1, u2);
  return mu + sigma * result.x1;  // On utilise x1 ici
}

int main() {
  srand(time(NULL));  // Initialisation du générateur pseudo-aléatoire
  
  double mu = 0;               // Moyenne souhaitée
  double sigma = pow(2, -3.19);  // Écart-type souhaité
  int n = 10000;

  for (int i = 0; i < n; i++) {
    double error = generate_normal_error(mu, sigma);
    printf("%f\n", error);
  }

  return 0;
}
