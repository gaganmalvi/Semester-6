/**
 * @file array-sum-parallel.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Parallel sum of array elements, using OpenMP functions
 * @date 2022-12-22
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/terminal.h"
#include "omp.h"

int main(int argc, char* argv[]) {
    int n = 0;
    printf(BLUE "[-] " RESET YELLOW "Enter the number of elements in the array: " RESET);
    scanf("%d", &n);

    long long int* arr = (long long int*)malloc(n * sizeof(long long int));
    printf(BLUE "[-] " RESET YELLOW "Enter the elements of the array: " RESET);
    for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

    long long int sum = 0;

    double time_1 = omp_get_wtime();

#pragma omp parallel for default(shared) reduction(+ : sum)
    for (int i = 0; i < n; i++) sum += arr[i];

    double time_2 = omp_get_wtime();

    printf(BLUE "[-] " RESET GREEN "Sum of the array elements: " RESET "%lld\n", sum);
    printf(BLUE "[-] " RESET GREEN "Time taken: " RESET "%g\n", time_2 - time_1);

    free(arr);

    return 0;
}
