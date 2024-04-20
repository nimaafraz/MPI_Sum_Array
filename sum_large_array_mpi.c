#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100  // Define the size of the array

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check if we have exactly four processes
    if (size != 4) {
        if (rank == 0) {
            printf("This program is designed to run with 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    // Allocate memory for the entire array only on the root process
    int *array = NULL;
    if (rank == 0) {
        array = (int *)malloc(ARRAY_SIZE * sizeof(int));
        // Initialize the array with random values
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 100;  // Random numbers between 0 and 99
        }
    }

    // Calculate the size of the sub-array each process will handle
    int sub_array_size = ARRAY_SIZE / size;

    // Allocate memory for the sub-array
    int *sub_array = (int *)malloc(sub_array_size * sizeof(int));

    // Scatter the array to all processes
    MPI_Scatter(array, sub_array_size, MPI_INT, sub_array, sub_array_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process calculates its partial sum
    int partial_sum = 0;
    for (int i = 0; i < sub_array_size; i++) {
        partial_sum += sub_array[i];
    }

    // Reduce all partial sums into the total sum
    int total_sum = 0;
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result from the root process
    if (rank == 0) {
        printf("Total sum of array elements is %d\n", total_sum);
        free(array);
    }

    // Free allocated memory
    free(sub_array);

    MPI_Finalize();
    return 0;
}

