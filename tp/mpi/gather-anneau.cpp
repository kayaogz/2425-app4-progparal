#include <iostream>
#include <vector>
#include "mpi.h"

using namespace std;

int MPI_GatherIntAnneau(
    const int *sendbuf,
    int count,
    int *recvbuf,
    int root,
    MPI_Comm comm)
{
  // A FAIRE ...
  return MPI_SUCCESS;
} 

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int elemsParProc = 5; // Taille de chaque petit tableau Aloc par processus apres Scatter
  int root = 1; // Processus root qui possede le tableau entier
  std::vector<int> Aloc(elemsParProc); // Petit tableau par processus
  std::vector<int> A; // Grand tableau, a allouer et initialiser dans le processus root
  for (int i = 0; i < elemsParProc; i++) { Aloc[i] = rank * elemsParProc + i; }
  if (rank == root) { 
    A.resize(elemsParProc * size, 0);
  }
  
  // Appeler MPI_GatherIntAnneau(...) sur A et Aloc, et avec la root. Tester contre MPI_Gather(...)
  // A FAIRE ...
//  MPI_GatherIntAnneau(...)
//  MPI_Gather(...)

  // Afficher Aloc pour chaque processus pour tester
  if (rank == root) { 
    for (auto i : A) { cout << i << endl; }
  }

  MPI_Finalize();

  return 0;
}
