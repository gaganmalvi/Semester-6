/**
 * @name hello-world.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Write a code using MPI to print "Hello World" from all processes
 * @date 2023-02-09
 */

#include <stdio.h>

#include "../include/terminal.h"
#include "mpi.h"

int main() {
    int world_size = 0;
    int world_rank = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len = 0;
    MPI_Get_processor_name(processor_name, &name_len);

    printf(BLUE "[-] " RESET GREEN
                "Hello world from processor %s, rank %d out of %d processors\n" RESET,
           processor_name, world_rank, world_size);

    MPI_Finalize();

    return 0;
}