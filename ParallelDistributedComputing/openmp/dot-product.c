/**
 * @file dot-product.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Perform dot product of two vectors using OpenMP
 * @date 2022-12-21
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/terminal.h"
#include "omp.h"

int main(int argc, char* argv[]) {
    int n = 0;

    double time_1 = omp_get_wtime();

    printf(GREEN "[-] Enter value of n: " RESET);
    scanf("%d", &n);

    long long int* a = (long long int*)malloc(n * sizeof(long long int));
    long long int* b = (long long int*)malloc(n * sizeof(long long int));

    printf(YELLOW "[+] Enter elements of vector a: " RESET);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

    printf(YELLOW "[+] Enter elements of vector b: " RESET);
    for (int i = 0; i < n; i++) scanf("%lld", &b[i]);

    long long int dot_product = 0;
#pragma omp parallel for reduction(+ : dot_product)
    for (int i = 0; i < n; i++) dot_product += a[i] * b[i];

    double time_2 = omp_get_wtime();

    printf(BLUE "[✓] Dot product of vectors a and b is: %lld\n" RESET, dot_product);
    printf(BLUE "[✓] Time taken: %g\n" RESET, time_2 - time_1);

    free(a);
    free(b);

    return 0;
}
