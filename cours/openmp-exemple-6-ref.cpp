#include <iostream>
#include <unistd.h>
#include "omp.h"

int calculDeux()
{
  sleep(2);
  return 2;
}

int calculTrois()
{
  sleep(3);
  return 3;
}

int calculQuatre()
{
  sleep(4);
  return 4;
}

int main()
{
  int deux, trois, quatre, cinq, neuf;
#pragma omp parallel num_threads(3) default(none) shared(deux, trois, quatre, neuf)
  {
    int thid = omp_get_thread_num();
    int numth = omp_get_num_threads();
    printf("Je suis thread %d/%d\n", thid, numth);
#pragma omp barrier

#pragma omp single
    {
      printf("thread %d cree les taches\n", thid);
#pragma omp task default(none) shared(deux, thid) depend(out:deux)
      {
        printf("thread %d execute calcul deux\n", thid);
        deux = calculDeux();
      }
#pragma omp task default(none) shared(trois) depend(out:trois)
      {
        printf("thread %d execute calcul trois\n", omp_get_thread_num());
        trois = calculTrois();
      }
#pragma omp task default(none) shared(quatre) depend(out:quatre)
      {
        printf("thread %d execute calcul quatre\n", omp_get_thread_num());
        quatre= calculQuatre();
      }
#pragma omp task default(none) shared(neuf, deux, trois, quatre) depend(in:deux,trois,quatre) depend(out:neuf)
      {
        printf("thread %d execute calcul neuf\n", omp_get_thread_num());
        neuf = deux + trois + quatre;
        printf("%d = %d %d %d\n", neuf, deux, trois, quatre);
      }
    }
/*#pragma omp taskwait
    neuf = deux + trois + quatre;
    printf("%d %d %d\n", deux, trois, quatre);
    printf("%d = %d %d %d\n", neuf, deux, trois, quatre);*/
  }

  return 0;
}
