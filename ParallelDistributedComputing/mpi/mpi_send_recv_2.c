/**
 * @file mpi_send_recv_2.c
 * @author Gagan Malvi <malvi@aospa.co>
 */

#include <stdio.h>

#include "mpi.h"
#include "../include/terminal.h"

void broadcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator) {
    int rank = 0;
    MPI_Comm_rank(communicator, &rank);

    int size = 0;
    MPI_Comm_size(communicator, &size);

    if (rank == root) {
        for (int i = 0; i < size; i++) {
            if (i != rank) {
                MPI_Send(data, count, datatype, i, 0, communicator);
            }
        }
    } else {
        MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
    }
}

int main() {
    MPI_Init(NULL, NULL);

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = 0;
    if (rank == 0) {
        data = 100;
        printf(BLUE "[-] " RESET GREEN "Process 0 broadcasting data %d\n" RESET, data);
        broadcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        broadcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf(BLUE "[-] " RESET GREEN "Process %d received number %d from process 0\n" RESET, rank, data);
    }

    MPI_Finalize();
}