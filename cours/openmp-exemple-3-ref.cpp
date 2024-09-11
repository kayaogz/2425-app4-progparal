#include <cstdio>
#include <unistd.h>
#include <vector>
#include "omp.h"

int main()
{
  std::vector<int> A(1000);

  for (int i = 0; i < A.size(); i++) {
    A[i] = 1;
  }

  std::vector<int> sommeTh(100);

  int somme = 0;

#pragma omp parallel num_threads(4) default(none) shared(A, sommeTh, somme)
  {
    int thid = omp_get_thread_num();
    int numth = omp_get_num_threads();
    printf("thid = %d/%d\n", thid, numth);
    int sommeLoc = 0;

#pragma omp for reduction(+:somme)
    for (int i = 0; i < A.size(); i++) {
      somme += A[i];
    } // Barriere implicite


//    for (int i = thid * (A.size() / numth); i < (thid + 1) * (A.size() / numth); i++) {
//      printf("i = %d, thid = %d\n", i, thid);
//      A[i] = i;
//      sommeLoc = sommeLoc + A[i];
//    }
//    sommeTh[thid] = sommeLoc;
//    printf("sommeLoc = %d, thid = %d\n", sommeLoc, thid);

//#pragma omp critical
//    {
//      somme += sommeTh[thid];
//    }

//#pragma omp atomic
//    somme += sommeTh[thid];

#pragma omp barrier

//#pragma omp barrier
//
//#pragma omp single
//    {
//      for (int i = 0; i < numth; i++) { 
//        somme += sommeTh[i];
//      }
//    } // Barriere implicite

//#pragma omp sections
//    {
//#pragma omp section
//      {
//        for (int i = 0; i < A.size() / 4; i++) { A[i] = i; }
//      }
//#pragma omp section
//      {
//        for (int i = A.size() / 4; i < 2 * A.size() / 4; i++) { A[i] = i; }
//      }
//#pragma omp section
//      {
//        for (int i = 2 * A.size() / 4; i < 3 * A.size() / 4; i++) { A[i] = i; }
//      }
//#pragma omp section
//      {
//        for (int i = 3 * A.size() / 4; i < A.size(); i++) { A[i] = i; }
//      }
//    }
  }
//  for (int i = 0; i < sommeTh.size(); i++) { 
//    somme += sommeTh[i];
//  }
  printf("somme = %d\n", somme);


//  for (int i = 0; i < A.size(); i++) {
//    printf("%d\n", A[i]);
//  }

  return 0;
}
