/** Exercice Ping-Pong
  * Compilation: mpic++ -O2 ping-pong-ref.cpp -o ping-pong
  * Execution(avec 7 processus): mpirun -np 7 ./ping-pong
  */
#include <cstdio>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int msg;
  if ((rank % 2 == 0) && (rank + 1 < size)) { // Le processus est pair et son binome existe
    msg = rank;
    printf("Processus %d message envoye au processus %d: %d\n", rank, rank + 1, msg);
    MPI_Send(&msg, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    MPI_Recv(&msg, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Processus %d message recu du processus %d: %d\n", rank, rank + 1, msg);
  } else if (rank % 2 == 1) { // Le processus est impair
    MPI_Recv(&msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    msg += 10 * rank;
    MPI_Send(&msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
