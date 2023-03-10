/**
 * @file vector-addition.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Perform vector addition of two vectors using OpenMP
 * @date 2022-12-21
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/terminal.h"
#include "omp.h"

int main(int argc, char* argv[]) {
    int n = 0;
    printf(RED "[-] Enter value of n: " RESET);
    scanf("%d", &n);

    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));
    int* c = (int*)malloc(n * sizeof(int));

    printf(YELLOW "[+] Enter elements of vector a: " RESET);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf(YELLOW "[+] Enter elements of vector b: " RESET);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

#pragma omp parallel for
    for (int i = 0; i < n; i++) c[i] = a[i] + b[i];

    printf(BLUE "[✓] Vector c is: " RESET);
    for (int i = 0; i < n; i++) printf("%d ", c[i]);

    printf("\n");

    free(a);
    free(b);
    free(c);

    return 0;
}
