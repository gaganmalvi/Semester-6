/**
 * @file default-example.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Write an OpenMP program that makes use of the default clause.
 */

#include <stdio.h>

#include "../include/terminal.h"
#include "omp.h"

int main() {
    int a = 0;
    int shared_variable = 0;

    int n = 0;
    printf(BLUE "[-] " RESET YELLOW "Enter the number of iterations: " RESET);
    scanf("%d", &n);

#pragma omp parallel for default(shared) private(a)
    for (int i = 0; i < n; i++) {
        a = i + 1;
        shared_variable = a;
        printf(BLUE "[-] " RESET GREEN "Thread %d: " RESET
                    "a = %d, shared_variable = %d (shared) when i = %d\n",
               omp_get_thread_num(), a, shared_variable, i);
    }

    printf(BLUE "[-] " RESET GREEN "shared_variable = %d (shared)\n" RESET, shared_variable);

    return 0;
}