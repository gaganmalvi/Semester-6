/**
 * @file dot-product.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Perform dot product of two vectors using OpenMP
 * @date 2022-12-21
 */

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "../include/terminal.h"

int main(int argc, char *argv[])
{
    int n = 0;
    printf(GREEN "[-] Enter value of n: " RESET);
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    printf(YELLOW "[+] Enter elements of vector a: " RESET);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    
    printf(YELLOW "[+] Enter elements of vector b: " RESET);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

    int dot_product = 0;
    #pragma omp parallel for reduction(+:dot_product)
    for (int i = 0; i < n; i++) dot_product += a[i] * b[i];

    printf(BLUE "[✓] Dot product of vectors a and b is: %d\n" RESET, dot_product);

    free(a);
    free(b);
    
    return 0;
}
