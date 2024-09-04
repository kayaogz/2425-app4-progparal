#include <iostream>
#include "omp.h"

#define N 16
#define K 4
#define NTASKS (N / K)

double A[N][N];
double B[N][N];
bool deps[NTASKS + 1][NTASKS + 1];

void printArray(double tab[N][N])
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%4.0lf ", tab[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char **argv)
{
  // Initialize the array A[i][j] = i + j in parallel.
  // Version 1: Using omp for loop. We can collapse two loops since each iteration (i, j) is independent
  // Version 1: Avec boucle omp for. On peut faire collapse pour deux boucles car chaque iteration (i, j) est
  // independante
  // TODO / A FAIRE ...
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      A[i][j] = i + j;

  // Version 2: Using tasks, each task initializes a block of size K x K. There are (N / K) x (N / K) tasks in total
  // Version 2: Avec taches, chaque tache initialise un bloc de taille K x K. Il y a (N / K) x (N / K) taches au total
  // TODO / A FAIRE ...

  if (N < 20) {
    printf("Array A:\n");
    printArray(A);
  }

  // 
#pragma omp parallel default(none) shared(A, B, deps)
  {
#pragma omp single
    {
      for (int ti = 0; ti < NTASKS; ti++) {
        for (int tj = 0; tj < NTASKS; tj++) {
#pragma omp task default(none) firstprivate(ti, tj) shared(A, B) \
          depend(out:deps[ti + 1][tj + 1]) depend(in:deps[ti][tj],deps[ti + 1][tj],deps[ti][tj + 1])
          for (int i = ti * K; i < (ti + 1) * K; i++) {
            for (int j = tj * K; j < (tj + 1) * K; j++) {
              if (i == 0) { 
                if (j == 0) {
                  B[i][j] = A[i][j];
                } else {
                  B[i][j] = B[i][j - 1] + A[i][j];
                }
              } else if (j == 0) {
                B[i][j] = B[i - 1][j] + A[i][j];
              } else {
                B[i][j] = B[i - 1][j] + B[i][j - 1] - B[i - 1][j - 1] + A[i][j];
              }
            }
          }
        }
      }
    }
  }
  if (N < 20) {
    printf("Array B:\n");
    printArray(B);
  }
  return 0;
}
