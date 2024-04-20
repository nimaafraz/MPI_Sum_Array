#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100  // Define the size of the array
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *array = NULL;
    int sub_array_size = ARRAY_SIZE / size;
    int *sub_array = (int *)malloc(sub_array_size * sizeof(int));
    int partial_sum = 0, total_sum = 0;

    if (rank == 0) {
        // Allocate and initialize the entire array only on the root process
        array = (int *)malloc(ARRAY_SIZE * sizeof(int));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 100;  // Random numbers between 0 and 99
        }

        // Send chunks of the array to each process
        for (int i = 1; i < size; i++) {
            MPI_Send(array + i * sub_array_size, sub_array_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        // Root process calculates its own partial sum
        for (int i = 0; i < sub_array_size; i++) {
            partial_sum += array[i];
        }
        total_sum = partial_sum;  // Start total_sum with root's partial sum

        // Receive partial sums from other processes and add to total sum
        for (int i = 1; i < size; i++) {
            MPI_Recv(&partial_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += partial_sum;
        }

        printf("Total sum of array elements is %d\n", total_sum);
        free(array);
    } else {
        // Receive sub-array from root process
        MPI_Recv(sub_array, sub_array_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Calculate partial sum for received sub-array
        for (int i = 0; i < sub_array_size; i++) {
            partial_sum += sub_array[i];
        }
        // Send partial sum back to the root process
        MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    free(sub_array);

    MPI_Finalize();
    return 0;
}


