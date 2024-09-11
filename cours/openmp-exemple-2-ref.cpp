#include <cstdio>
#include <unistd.h>
#include "omp.h"

int calcul2()
{
  sleep(2);
  return 2;
};

int calcul3()
{
  sleep(3);
  return 3;
};

int calcul4()
{
  sleep(4);
  return 4;
};

int main()
{
  int deux, trois, quatre, neuf;

#pragma omp parallel num_threads(3) default(none) shared(deux, trois, quatre)
  {
    int thid = omp_get_thread_num();
    int numth = omp_get_num_threads();
    printf("thid = %d/%d\n", thid, numth);

#pragma omp sections
    {
#pragma omp section
      {
        printf("calcul deux fait par thid = %d/%d\n", thid, numth);
        deux = calcul2();
      }
#pragma omp section
      {
        printf("calcul trois fait par thid = %d/%d\n", thid, numth);
        trois = calcul3();
      }
#pragma omp section
      {
        printf("calcul fait par thid = %d/%d\n", thid, numth);
        quatre = calcul4();
      }
    }
  }

  neuf = deux + trois + quatre;

  printf("neuf = %d\n", neuf);

  return 0;
}
