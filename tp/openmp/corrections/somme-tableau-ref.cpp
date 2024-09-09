#include <chrono>
#include <iostream>
#include <vector>
#include "omp.h"

int main()
{
  int i;
  int N = 10000000;
  std::vector<double> A(N);
  double somme = 0.0;

  auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel default(none) num_threads(4) shared(somme, A, N, i)
  {
#pragma omp for
    for (i = 0; i < N; i++) {
      A[i] = (double)i;
    } // barrier implicite
    
    // somme partagee
//#pragma omp for reduction(+:somme)
//    for (i = 0; i < N; i++) {
//      somme += A[i];
//    }
    
#pragma omp sections
    {
#pragma omp section
      {
        double sommeLocale = 0;
        for (int i = 0; i < N / 4; i++) { sommeLocale += A[i]; }
#pragma omp atomic
          somme += sommeLocale;
      }
#pragma omp section
      {
        double sommeLocale = 0;
        for (int i = N / 4; i < (2 * N) / 4; i++) { sommeLocale += A[i]; }
#pragma omp atomic
        somme += sommeLocale;
      }
#pragma omp section
      {
        double sommeLocale = 0;
        for (int i = (2 * N) / 4; i < (3 * N) / 4; i++) { sommeLocale += A[i]; }
#pragma omp atomic
        somme += sommeLocale;
      }
#pragma omp section
      {
        double sommeLocale = 0;
        for (int i = (3 * N) / 4; i < N; i++) { sommeLocale += A[i]; }
#pragma omp atomic
        somme += sommeLocale;
      }
    }
  }
  std::cout << "La somme est " << somme << std::endl;
  std::chrono::duration<double> temps = std::chrono::high_resolution_clock::now() - start;
  std::cout << "Temps de calcul: " << temps.count() << "s\n";

  return 0;
}
