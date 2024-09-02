#include <iostream>
#include <vector>
#include "mpi.h"

using namespace std;

int GatherInt(
    const int *sendbuf,
    int count,
    int *recvbuf,
    int root,
    MPI_Comm comm)
{
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  std::vector<MPI_Request> request(size, MPI_REQUEST_NULL);
  if (rank == root) {
    for (int proc = 0; proc < size; proc++) {
      if (proc == rank) { 
        for (int i = 0; i < count; i++) {recvbuf[proc * count + i] = sendbuf[i]; }
      } else { MPI_Irecv(&recvbuf[proc * count], count, MPI_INT, proc, 0, MPI_COMM_WORLD, &request[proc]); }
    }
    MPI_Waitall(size, &request[0], MPI_STATUSES_IGNORE);
  } else { MPI_Send(sendbuf, count, MPI_INT, root, 0, MPI_COMM_WORLD); }
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
  
  // Appeler GatherInt(...) sur A et Aloc, et avec la root. Tester contre MPI_Gather(...)
  GatherInt(&Aloc[0], elemsParProc, &A[0], root, MPI_COMM_WORLD);
//  MPI_Gather(&Aloc[0], elemsParProc, MPI_INT, &A[0], elemsParProc, MPI_INT, root, MPI_COMM_WORLD);

  // Afficher Aloc pour chaque processus pour tester
  if (rank == root) { 
    for (auto i : A) { cout << i << endl; }
  }

  MPI_Finalize();

  return 0;
}
