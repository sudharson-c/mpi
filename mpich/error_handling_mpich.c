#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    int world_rank;
    MPI_Status status;

    int provided;
    MPI_Query_thread(&provided);
    if (provided < MPI_THREAD_SINGLE) {
        fprintf(stderr, "Error: MPI_THREAD_SINGLE required, but provided %d\n", provided);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (MPI_Comm_size(MPI_COMM_WORLD, &world_size) != MPI_SUCCESS) {
        fprintf(stderr, "Error: Failed to get communicator size\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (MPI_Comm_rank(MPI_COMM_WORLD, &world_rank) != MPI_SUCCESS) {
        fprintf(stderr, "Error: Failed to get process rank\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (world_size < 2) {
        fprintf(stderr, "Error: At least two processes are required.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (world_rank == 0) {
        int data = 100;
        int err = MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        if (err != MPI_SUCCESS) {
            char error_string[MPI_MAX_ERROR_STRING];
            int length_of_error_string;
            MPI_Error_string(err, error_string, &length_of_error_string);
            fprintf(stderr, "Error in MPI_Send: %s\n", error_string);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
    } else if (world_rank == 1) {
        int data = 0;  // Initialize data
        int err = MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        if (err != MPI_SUCCESS) {
            char error_string[MPI_MAX_ERROR_STRING];
            int length_of_error_string;
            MPI_Error_string(err, error_string, &length_of_error_string);
            fprintf(stderr, "Error in MPI_Recv: %s\n", error_string);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        printf("Received data: %d\n", data);
    }

    MPI_Finalize();
    return 0;
}
