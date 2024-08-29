#include <chrono>
#include <iostream>
#include "mpi.h"

inline double f(double x)
{
  return (4.0 / (1 + x * x));
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int i;
  const int N = 100000000;
  double pi = 0.0;
  double s = 1.0 / (double)N;

  // Calculer le pi en parallele
  // A FAIRE ...
  int rank, size;


  // Afficher le pi
  if (rank == 0) { printf("Pi: %lf\n", pi); }

  MPI_Finalize();
  return 0;
}
