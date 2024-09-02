#include <iostream>
#include <vector>
#include "mpi.h"

using namespace std;

int MPI_BcastAnneau(
    void *buf,
    int count,
    MPI_Datatype type,
    int root,
    MPI_Comm comm)
{
  // A FAIRE ...
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size > 1) {
    int prev = (rank + size - 1) % size;
    int next = (rank + 1) % size;
    if (rank != root) { // Root fait un send et non pas un recv
      MPI_Recv(buf, count, type, prev, 0, comm, MPI_STATUS_IGNORE);
    }
    if (next != root) { // Avant root fait un recv et non pas send
      MPI_Send(buf, count, type, next, 0, comm);
    }
  }
  return MPI_SUCCESS;
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int root = 1; // Processus root qui possede le tableau entier
  int N = 4; // La taille du tableau a broadcaster
  std::vector<int> A(N); // Grand tableau, a initialiser que dans le processus root
  if (rank == root) { 
    for (int i = 0; i < N; i++) { A[i] = i; }
  }
  
  // Appeler MPI_BcastAnneau(...) sur A, et avec la root. Tester contre MPI_Bcast(...)
  // A FAIRE ...
  MPI_BcastAnneau(&A[0], N, MPI_INT, root, MPI_COMM_WORLD);
//  MPI_Bcast(&A[0], N, MPI_INT, root, MPI_COMM_WORLD);

  // Afficher A pour chaque processus pour tester
  for (auto i : A) { cout << i << ":" << rank << endl; }

  MPI_Finalize();

  return 0;
}
