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

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // N, size :  (0...N/size - 1) (N/size ... 2N/size - 1) (...)
  int begin = (N / size) * rank;
  int end = (rank == size - 1) ? N : (N / size) * (rank + 1);
  double piLocal = 0.0;
  for (int i = begin; i < end; i++) {
    piLocal += s * (f(i * s) + f((i + 1) * s)) / 2;
  }
  if (rank == 0) {
    pi = piLocal;
    for (int i = 1; i < size; i++) {
      MPI_Recv(&piLocal, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      pi += piLocal;
    }
    for (int i = 1; i < size; i++) {
      MPI_Send(&pi, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    }
  } else {
      MPI_Send(&piLocal, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Rank: %d, pi: %lf\n", rank, pi);
  }
//  MPI_Reduce(&piLocal, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) { printf("Pi: %lf\n", pi); }

  MPI_Finalize();
  return 0;
}
