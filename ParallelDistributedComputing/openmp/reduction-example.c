/**
 * @file reduction-example.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Write an OpenMP program that makes use of the reduction clause.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/terminal.h"
#include "omp.h"

int main() {
    int n = 0;
    printf(BLUE "[-] " RESET YELLOW "Enter the number of elements in the array: " RESET);
    scanf("%d", &n);

    int *array = (int *)malloc(n * sizeof(int));
    printf(BLUE "[-] " RESET YELLOW "Enter the elements of the array: " RESET);
    for (int i = 0; i < n; i++) scanf("%d", &array[i]);

    int sum = 0;
    #pragma omp parallel for default(shared) reduction(+ : sum)
    for (int i = 0; i < n; i++) sum += array[i];

    printf(BLUE "[-] " RESET GREEN "Sum of the array elements: " RESET "%d\n", sum);

    free(array);

    return 0;
}