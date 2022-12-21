/**
 * @file dot-product.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Perform dot product of two vectors using OpenMP
 */

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(int argc, char *argv[])
{
    int n = 0;
    printf("[-] Enter value of n: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    printf("[+] Enter elements of vector a: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    
    printf("[+] Enter elements of vector b: ");
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);

    int dot_product = 0;
    #pragma omp parallel for reduction(+:dot_product)
    for (int i = 0; i < n; i++) dot_product += a[i] * b[i];

    printf("[✓] Dot product of vectors a and b is: %d\n", dot_product);

    free(a);
    free(b);
    
    return 0;
}