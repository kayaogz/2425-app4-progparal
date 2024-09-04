#include <cstdio>
#include <unistd.h>

int main()
{

#pragma omp parallel num_threads(3) default(none)
  {
    printf("Hello\n");
  }

  printf("Hello seq\n");

  return 0;
}
