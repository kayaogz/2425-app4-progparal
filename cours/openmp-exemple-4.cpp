#include <cstdio>
#include "omp.h"

int main()
{
#pragma omp parallel num_threads(2)
  {
#pragma omp single
#pragma omp task
    {
      printf("Hello\n");
    }
  }
  return 0;
}
