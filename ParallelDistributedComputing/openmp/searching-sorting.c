/**
 * @file searching-sorting.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Searching in, and sorting of an array (parallelized) using OpenMP, using the n-ary search
 * algorithm
 * @date 2023-01-19
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/terminal.h"
#include "omp.h"

typedef struct Compare {
    long long int value;
    int index;
} Compare;

#pragma omp declare reduction(maximum                                                      \
                              : struct Compare                                             \
                              : omp_out = omp_in.value > omp_out.value ? omp_in : omp_out) \
        initializer(omp_priv = omp_orig)

void selection_sort_parallelized(long long int* arr, int n) {
    for (int i = n - 1; i > 0; --i) {
        Compare max;
        max.value = arr[i];
        max.index = i;

#pragma omp parallel for reduction(maximum : max)
        for (int j = i - 1; j >= 0; --j) {
            if (arr[j] > max.value) {
                max.value = arr[j];
                max.index = j;
            }
        }
        long long int tmp = arr[i];
        arr[i] = max.value;
        arr[max.index] = tmp;
    }
}

void parallel_linear_search(long long int* arr, int n, long long int key) {
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            printf(BLUE "[✓] " RESET GREEN "Thread %d found element %lld at index %d\n" RESET,
                   omp_get_thread_num(), key, i);
}

int binary_search_chunk(long long int* arr, long long int key, int start, int end) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}

void parallel_binary_search(long long int* arr, long long int key, int size) {
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int chunk_size = size / num_threads;
        int start = id * chunk_size;
        int end = (id == num_threads - 1) ? size - 1 : start + chunk_size - 1;
        int index = binary_search_chunk(arr, key, start, end);
        if (index != -1)
            printf(BLUE "[✓] " RESET GREEN "Thread %d found element %lld at index %d\n" RESET, id,
                   key, index);
    }
}

int main() {
    int n = 0;
    double time_1 = 0, time_2 = 0;
    long long int key = 0;

    printf(BLUE "[-] " RESET YELLOW "Enter number of elements in the array: " RESET);
    scanf("%d", &n);

    long long int* arr = (long long int*)malloc(n * sizeof(long long int));
    printf(BLUE "[-] " RESET YELLOW "Enter the elements of the array: " RESET);
    for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

    time_1 = omp_get_wtime();
    selection_sort_parallelized(arr, n);
    time_2 = omp_get_wtime();

    printf(BLUE "[✓] " RESET GREEN "Sorted array: " RESET);
    for (int i = 0; i < n; i++) printf("%lld ", arr[i]);
    printf("\n");

    printf(BLUE "[✓] " RESET GREEN "Time taken: %g\n" RESET, time_2 - time_1);

    printf("\n");

    printf(BLUE "[!] " RESET YELLOW "Linear Search\n" RESET);
    printf(BLUE "[-] " RESET YELLOW "Enter the element to search for: " RESET);
    scanf("%lld", &key);

    time_1 = omp_get_wtime();
    parallel_linear_search(arr, n, key);
    time_2 = omp_get_wtime();

    printf(BLUE "[✓] " RESET GREEN "Time taken: %g\n" RESET, time_2 - time_1);

    printf("\n");

    printf(BLUE "[!] " RESET YELLOW "Binary Search\n" RESET);
    printf(BLUE "[-] " RESET YELLOW "Enter the element to search for: " RESET);
    scanf("%lld", &key);

    time_1 = omp_get_wtime();
    parallel_binary_search(arr, key, n);
    time_2 = omp_get_wtime();

    printf(BLUE "[✓] " RESET GREEN "Time taken: %g\n" RESET, time_2 - time_1);

    free(arr);
}