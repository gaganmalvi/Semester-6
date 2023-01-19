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
    int thread_id = 0;
#pragma omp parallel private(thread_id)
    {
        thread_id = omp_get_thread_num();
        printf(BLUE "[-] " RESET YELLOW "Thread %d is waiting at the barrier.\n" RESET, thread_id);
#pragma omp barrier
        printf(BLUE "[✓] " RESET GREEN "Thread %d has passed the barrier.\n" RESET, thread_id);
    }
}