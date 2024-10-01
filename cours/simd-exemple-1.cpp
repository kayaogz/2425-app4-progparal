#include <cstdio>
#include "immintrin.h"

int main()
{
  float A[8] = {0, 2, 4, 6, 8, 10, 12, 14};
  int perm[8] = {1, 2, 3, 4, 5, 6, 7, 0};

// Pour faire ce calcul
// for (i = 0; i < 8; i++)
//   B[i] = A[perm[i]];

  __m256 va;
  __m256i vidx; 

  va = _mm256_loadu_ps(&A[0]);
  vidx = _mm256_loadu_si256((const __m256i_u*)&perm[0]);
  va = _mm256_permutevar8x32_ps(va, vidx);
  _mm256_storeu_ps(&A[0], va);

  for (int i = 0; i < 8; i++) { printf("%f ", A[i]); }
  printf("\n"); 

  return 0;
}
