/**
 * @file no-loop-carried-dependency.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Write a code using OpenMP to make the loop iterations independent 
 *        to safely execute in any order without loop carried dependency
 * @date 2023-02-01
 */

#include <stdio.h>
#include <stdlib.h>

#include "omp.h"
#include "../include/terminal.h"

int main() {
    int n = 0;
    printf(BLUE "[-] " RESET RED "Enter the number of iterations: " RESET);
    scanf("%d", &n);

    printf(BLUE "[-] " RESET GREEN "Loop iterations: " RESET "\n");
    printf(BLUE "[-] " RESET GREEN "Starting on number of threads: " RESET "%d\n", omp_get_max_threads());

    int* arr = (int*)malloc(n * sizeof(int));
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = 5 + 2 * i;
        printf(BLUE "[-] " RESET GREEN "Iteration %d: " RESET "%d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}