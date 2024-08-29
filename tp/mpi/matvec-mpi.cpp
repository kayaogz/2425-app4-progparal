#include <iostream>
#include <cstdlib>
#include "mpi.h"

int main(int argc, char **argv)
{
  int rank, size;
  int N = 32;
  double *A, *x, *b;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Allouer x et b dans tous les processus 
  b = (double *)malloc(N * sizeof(double));
  x = (double *)malloc(N * sizeof(double));
  // Allouer A, puis initialiser A et x dans le processus 0
  if (rank == 0) {
    A = (double *)malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
      x[i] = 1.0;
      for (int j = 0; j < N; j++) { 
        A[i * N + j] = i + j; // On accede a A(i, j) par A[i * N + j] car A est orientee par des lignes
      }
    }
  }

  // Distribuer A dans les processus tel que chaque processus recoit N / size lignes de A dans Alocal
  // A FAIRE ...
  double *Alocal;

  // Distribuer x entier dans tous les processus
  // A FAIRE ...

  // Effectuer le produit matrice-vecteur local dans blocal
  // A FAIRE ...
  double *blocal;

  // Mettre ensemble le resultat b dans tous les processus
  // A FAIRE ...

  // Verifier le resultat dans tous les processus
  for (int i = 0; i < N; i++) {
    double val = (N - 1) * (double)N / 2.0 + (double)i * N;
    if (b[i] != val) {
      std::cout << "valeur incorrecte: proc " << rank << " b[" << i << "] = " << b[i] << " != " << val << std::endl;
      break;
    }
    if (i == N - 1) {
      std::cout << "Produit matrice-vecteur est effectue avec succes dans le processus " << rank << "!\n";
    }
  }

  // Desallouer A, x et b
  free(b);
  free(x);
  if (rank == 0) { free(A); }

  MPI_Finalize();
  return 0;
}
