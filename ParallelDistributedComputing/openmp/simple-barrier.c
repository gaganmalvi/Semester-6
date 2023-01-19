/**
 * @file simple-barrier.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Simple barrier implementation using OpenMP
 * @date 2023-01-19
 */

#include <stdio.h>
#include "omp.h"
#include "../include/terminal.h"

int main() {
#pragma omp parallel for
    for (int i = 0; i < omp_get_max_threads(); i++) {
        int thread_id = omp_get_thread_num();
        if (thread_id == i) {
            printf(BLUE "[-] " RESET GREEN "Thread %d is executing\n" RESET, thread_id);
        }
    }
#pragma omp barrier
    return 0;
}