#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
int rank, size;
char send_data[25] = "Hi, Nice to catch up with you";
char recv_data[25];
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if (size != 2) {
if (rank == 0) {
printf("This program requires exactly 2 MPI processes.\n");
}
MPI_Abort(MPI_COMM_WORLD, 1);
}
if (rank == 0) {
printf("Process %d: Sending data %s\n", rank, send_data);
MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
} else if (rank == 1) {
MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
MPI_STATUS_IGNORE);
printf("Process %d: Received data %s\n", rank, recv_data);}
}
MPI_Finalize(); return 0;}
