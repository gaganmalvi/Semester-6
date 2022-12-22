/**
 * @file introduction.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Introduction to OpenMP
 * @date 2022-12-22
 */

#include <stdio.h>
#include "omp.h"
#include "../include/terminal.h"

int main(int argc, char *argv[])
{
    #pragma omp parallel
    {
        int nthreads = omp_get_num_threads();
        int id = omp_get_thread_num() + 1;
        printf(RED "Hello World from thread " RESET BLUE "[%d] of [%d] \n" RESET, id, nthreads);
    }

    return 0;
}
