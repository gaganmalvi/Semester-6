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
    printf(BLUE "[-] " RESET RED "Enter the number of elements in the array: " RESET);
    scanf("%d", &n);

    long long int* arr = (long long int*)malloc(n * sizeof(long long int));
    printf(BLUE "[-] " RESET YELLOW "Enter the elements of the array: " RESET);
    for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

    long long int sum = 0;

#pragma omp parallel for default(shared) reduction(+ : sum)
    for (int i = 0; i < n; i++) sum += arr[i];

    printf(BLUE "[-] " RESET GREEN "Sum of the array elements: " RESET "%lld\n", sum);

    free(arr);

    return 0;
}
