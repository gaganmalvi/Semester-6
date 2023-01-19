/**
 * @file simple-critical.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Simple critical section implementation using OpenMP
 * @date 2023-01-19
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/terminal.h"
#include "omp.h"

int main(int argc, char** argv) {
    int global_nloops = 0, priv_nloops = 0;
    int thread_id = 0;
    int iterations = argv[1] ? atoi(argv[1]) : 10;
#pragma omp parallel private(priv_nloops, thread_id)
    {
        priv_nloops = 0;

#pragma omp for
        for (int i = 0; i < iterations; i++) {
            thread_id = omp_get_thread_num();
            ++priv_nloops;

#pragma omp critical
            {
                printf(BLUE "[-] " RESET YELLOW
                            "Thread %d is adding priv_nloops (%d) to glob_nloops (%d).\n" RESET,
                       thread_id, priv_nloops, global_nloops);
                global_nloops += priv_nloops;
                printf(BLUE "[✓] " RESET GREEN "global_nloops = %d\n", global_nloops);
            }
        }
    }
}