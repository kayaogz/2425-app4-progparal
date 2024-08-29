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

  if (rang == 0) {
    deux = calcul2();
    MPI_Recv(&trois, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cinq = deux + trois;
    MPI_Send(&cinq, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }

  else if (rang == 1) {
    trois = calcul3();
    MPI_Send(&trois, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Recv(&cinq, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }


  printf("cinq = %d\n", cinq);

  MPI_Finalize();
  return 0;
}
