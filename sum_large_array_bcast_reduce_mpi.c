#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000  // Define the size of the array

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    int sub_array_size = ARRAY_SIZE / size;
    int partial_sum = 0, total_sum = 0;

    if (rank == 0) {
        // Initialize the array only on the root process
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 100;  // Random numbers between 0 and 99
        }
    }

    // Broadcast the entire array to all processes
    MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate partial sum for each process's assigned portion
    int start_index = rank * sub_array_size;
    int end_index = (rank + 1) * sub_array_size;
    for (int i = start_index; i < end_index; i++) {
        partial_sum += array[i];
    }

    // Use MPI_Reduce to sum up all partial sums at the root process
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the total sum
    if (rank == 0) {
        printf("Total sum of array elements is %d\n", total_sum);
    }

    free(array);

    MPI_Finalize();
    return 0;
}

