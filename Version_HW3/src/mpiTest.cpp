// writing a small program to test the MPI library
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int num_procs, my_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("Hello from process %d of %d\n", my_rank, num_procs);

    MPI_Finalize();
    return 0;
}