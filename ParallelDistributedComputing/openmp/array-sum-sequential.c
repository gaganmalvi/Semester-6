/**
 * @file array-sum-sequential.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Sequential sum of array elements, using OpenMP functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/terminal.h"

int main(int argc, char *argv[])
{
    int n = 0;
    printf(BLUE "[-] " RESET RED "Enter the number of elements in the array: " RESET);
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf(BLUE "[-] " RESET YELLOW "Enter the elements of the array: " RESET);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];

    printf(BLUE "[-] " RESET GREEN "Sum of the array elements: " RESET "%d\n", sum);

    return 0;
}