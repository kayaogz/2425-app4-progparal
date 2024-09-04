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

#pragma omp parallel num_threads(2) default(none) shared(deux, trois, quatre)
  {
    int thid = omp_get_thread_num();
    int numth = omp_get_num_threads();
    printf("thid = %d/%d\n", thid, numth);

    if (thid == 0) {
      deux = calcul2();
    } else if (thid == 1) {
      trois = calcul3();
    } else if (thid == 2) {
      quatre = calcul4();
    }
  }

  neuf = deux + trois + quatre;

  printf("neuf = %d\n", neuf);

  return 0;
}
