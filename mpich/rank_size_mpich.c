 #include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[] ){
MPI_Init(&argc,&argv);
int size, rank;
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank); printf("Hello World!");
printf("\nSize: %d",size);printf("\nRank: %d",rank); MPI_Finalize();
