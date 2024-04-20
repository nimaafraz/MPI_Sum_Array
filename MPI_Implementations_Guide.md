
# COMP3036J Parallel and Cluster Computing: MPI Implementations for Array Summation
## Author: Nima Afraz
## Overview
This document provides instructions for compiling and running four different MPI implementations to sum the elements of a large array. Each implementation uses a different combination of MPI operations.

## Implementations
1. **Point-to-Point Only**
2. **Send/Recv for Segment Distribution**
3. **Broadcast Entire Array**
4. **Broadcast with Reduce**

# MPI Implementations Comparison Table

This table compares four MPI implementations based on various features to understand their differences in communication strategies.

## Comparison Table

| Feature/Implementation             | Point-to-Point Only                          | Send/Recv for Segment Distribution            | Broadcast Entire Array                       | Broadcast with Reduce                        |
|------------------------------------|---------------------------------------------|----------------------------------------------|---------------------------------------------|---------------------------------------------|
| **Communication Strategy**         | Direct send and recv for segments and sums | Direct send and recv for segments only, followed by manual collection of results | bcast used for distributing data, send and recv for collecting results | bcast for distribution, reduce for summing results |
| **Data Distribution**              | Sends only the required segment to each process | Sends only the required segment to each process | Sends the entire array to all processes     | Sends the entire array to all processes     |
| **Memory Usage per Process**       | Low (each process holds only its segment)   | Low (each process holds only its segment)    | High (each process holds the entire array)  | High (each process holds the entire array)  |



## Installation and files

Download zip file from Moodle or 

 ```bash
git clone https://github.com/nimaafraz/MPI_Sum_Array.git
  ```

## Compilation and Execution

### 1. Point-to-Point Only
- **Source File**: `sum_large_array_p2p_only_mpi.c`
- **Compile Command**:
  ```bash
  mpicc -o sum_large_array_p2p_only_mpi sum_large_array_p2p_only_mpi.c
  ```
- **Run Command**:
  ```bash
  mpirun -np 4 ./sum_large_array_p2p_only_mpi
  ```

### 2. Send/Recv for Segment Distribution
- **Source File**: `sum_large_array_send_recv_mpi.c`
- **Compile Command**:
  ```bash
  mpicc -o sum_large_array_send_recv_mpi sum_large_array_send_recv_mpi.c
  ```
- **Run Command**:
  ```bash
  mpirun -np 4 ./sum_large_array_send_recv_mpi
  ```

### 3. Broadcast Entire Array
- **Source File**: `sum_large_array_bcast_mpi.c`
- **Compile Command**:
  ```bash
  mpicc -o sum_large_array_bcast_mpi sum_large_array_bcast_mpi.c
  ```
- **Run Command**:
  ```bash
  mpirun -np 4 ./sum_large_array_bcast_mpi
  ```

### 4. Broadcast with Reduce
- **Source File**: `sum_large_array_bcast_reduce_mpi.c`
- **Compile Command**:
  ```bash
  mpicc -o sum_large_array_bcast_reduce_mpi sum_large_array_bcast_reduce_mpi.c
  ```
- **Run Command**:
  ```bash
  mpirun -np 4 ./sum_large_array_bcast_reduce_mpi
  ```



## Notes
- Replace `4` in the `mpirun` command with the number of processes you wish to use.
- Ensure MPI is installed and properly configured on your system or alternatively use the **Beckett4** server.



