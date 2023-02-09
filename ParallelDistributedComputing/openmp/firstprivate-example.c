/**
 * @name firstprivate-example.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Write an OpenMP program that makes use of the private, firstprivate and lastprivate
 * clause.
 */

#include <omp.h>
#include <stdio.h>

int main() {
    int i = 0;
    int x = 50;

#pragma omp parallel for private(x)
    for (i = 0; i < 10; i++) {
        x = i;
        printf("Thread %d: x = %d (private)\n", omp_get_thread_num(), x);
    }

    printf("x is %d\n", x);

#pragma omp parallel for firstprivate(x)
    for (i = 0; i < 10; i++) {
        x = i;
        printf("Thread %d: x = %d (firstprivate)\n", omp_get_thread_num(), x);
    }

    printf("x is %d\n", x);

#pragma omp parallel for lastprivate(x)
    for (i = 0; i < 10; i++) {
        x = i;
        printf("Thread %d: x = %d (lastprivate)\n", omp_get_thread_num(), x);
    }

    printf("x is %d\n", x);

    return 0;
}