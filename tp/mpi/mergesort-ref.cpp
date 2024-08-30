#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <chrono>
#include <mpi.h>

void assert(const std::vector<double>&);
void merge(double*, const double*, const int, const double*, const int); 

void printUsage(int argc, char **argv)
{
  printf("Usage: ./%s [array-size]\n", argv[0]);
}

int N;
int rank, size;

int main(int argc, char ** argv)
{
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (argc < 2) {
    if (rank == 0) { printUsage(argc, argv); }
    return 1;
  }


  // Initialiser le sous-tableau aleatoirement
  N = std::atoi(argv[1]);
  std::srand(std::time(0));
  std::vector<double> A(N);
  for (int i = 0; i < N; i++) { A[i] = std::rand() % 10000; } 

  // Tri le sous-tableaux
  std::sort(&A[0], &A[N]);

  // Fusionner les sous-tableaux dans le processus 0
  int count = N;
  for(int r = size; r > 1; r=r/2) {
    if(rank < r / 2) { // Je receive de mon partenaire puis je fusionne 
      int partner = rank+r/2;
      std::vector<double> tempRecv(count);
      std::vector<double> tempMerge(count + count);
      MPI_Recv(&tempRecv[0], count, MPI_DOUBLE, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
      merge(&tempMerge[0], &A[0], count, &tempRecv[0], count); 
      count *= 2;
      std::swap(A, tempMerge);
    } else if (rank >= r / 2 && rank < r) { // Je send a mon partenaire 
      int partner = rank-r/2;
      MPI_Send(&A[0], count, MPI_DOUBLE, partner, 0, MPI_COMM_WORLD); 
      break;
    }
  }
  
  // Verifier le tableau trie
  if(rank == 0) { assert(A); }
  MPI_Finalize();
  return 0;
}

void assert(const std::vector<double> & A) {
  if (A.size() != N * size) {
    std::cout << "Ça ne marche pas; la taille de A n'est pas bonne ! :(" << std::endl;
    return;
  }
  for (int i = 1; i < A.size(); i++) {
    if (A[i] < A[i-1]) {
      std::cout << "Ça ne marche pas; A n'est pas trie! :(" << std::endl;
      return;
    }
  }
  std::cout << "Ça marche les cocos ! " << std::endl;
}

void merge(double * res,
    const double * tabA,
    const int sizeA,
    const double * tabB,
    const int sizeB)
{
  int i = 0, j = 0;
  while(i != sizeA && j != sizeB ) {
    if (tabA[i] < tabB[j]) {
      res[i+j] = tabA[i];
      i++;
    } else {
      res[i+j] = tabB[j];
      j++;
    }
  }
  if (i == sizeA) {
    for(; j < sizeB; j++) {
      res[i+j] = tabB[j];
    }
  } else {
    for(; i < sizeA; i++) {
      res[i+j] = tabA[i];
    }
  }
}
