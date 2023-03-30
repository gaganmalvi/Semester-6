/**
 * @file mpi_send_recv.c
 * @author Gagan Malvi <malvi@aospa.co>
 */

#include <stdio.h>

#include "mpi.h"
#include "../include/terminal.h"

int main() {
    MPI_Init(NULL, NULL);

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number = 0;
    if (rank == 0) {
        number = 42;
        printf(BLUE "[-] " RESET GREEN "Process 0 broadcasting data %d\n" RESET, number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf(BLUE "[-] " RESET GREEN "Process 1 received number %d from process 0\n" RESET, number);
    }

    MPI_Finalize();
}