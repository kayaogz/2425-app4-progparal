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

int calcul4()
{
  sleep(4);
  return 4;
}


int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rang, size;
  int deux = 0, trois = 0, quatre = 0, cinq = 0, neuf = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &rang);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("%d/%d\n", rang, size);

  if (rang == 0) {
    deux = calcul2();
//    MPI_Recv(&trois, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//    MPI_Recv(&quatre, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//    neuf = deux + trois + quatre;
//    MPI_Send(&neuf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
//    MPI_Send(&neuf, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

//    MPI_Reduce(&deux, &neuf, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//    MPI_Bcast(&neuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Allreduce(&deux, &neuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  }

  else if (rang == 1) {
    trois = calcul3();
//    MPI_Send(&trois, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//    MPI_Recv(&neuf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

//    MPI_Reduce(&trois, NULL, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//    MPI_Bcast(&neuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Allreduce(&trois, &neuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  }

  else if (rang == 2) {
    quatre = calcul4();
//    MPI_Send(&quatre, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//    MPI_Recv(&neuf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

//    MPI_Reduce(&quatre, NULL, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//    MPI_Bcast(&neuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Allreduce(&quatre, &neuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  }


  printf("neuf = %d\n", neuf);

  MPI_Finalize();
  return 0;
}
