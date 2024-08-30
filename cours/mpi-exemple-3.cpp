#include <cstdio>
#include <unistd.h>
#include "mpi.h"

int calcul2()
{
  sleep(2);
  return 2;
}

int calcul3()
{
  sleep(3);
  return 3;
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rang, size;
  int deux = 0, trois = 0, cinq = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &rang);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("%d/%d\n", rang, size);
  MPI_Request request, request2;

  if (rang == 0) {
    deux = calcul2();
    MPI_Irecv(&trois, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    MPI_Send(&deux, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    cinq = deux + trois;
  }

  else if (rang == 1) {
    trois = calcul3();

    MPI_Irecv(&deux, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    MPI_Send(&trois, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    cinq = deux + trois;
  }


  printf("cinq = %d\n", cinq);

  MPI_Finalize();
  return 0;
}
