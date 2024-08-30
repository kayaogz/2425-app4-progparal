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
  int res;

  MPI_Comm_rank(MPI_COMM_WORLD, &rang);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("%d/%d\n", rang, size);

  if (rang == 0) { res = calcul2(); }
  if (rang == 1) { res = calcul3(); }
  if (rang == 2) { res = calcul4(); }

//  MPI_Barrier(MPI_COMM_WORLD);
  printf("res= %d\n", res);

  MPI_Allreduce(&res, &neuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  printf("neuf = %d\n", neuf);

  MPI_Finalize();
  return 0;
}
