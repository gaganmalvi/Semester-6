/**
 * @file searching-sorting.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Searching in, and sorting of an array (parallelized) using OpenMP
 * @date 2023-01-19
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/terminal.h"
#include "omp.h"

/**
 * @brief Structure to store the maximum value and its index
 */
typedef struct Compare {
    long long int value;
    int index;
} Compare;

/**
 * @brief Parallelized selection sort
 *
 * @param arr Array to sort
 * @param n Size of the array
 */
#pragma omp declare reduction(maximum                                                      \
                              : struct Compare                                             \
                              : omp_out = omp_in.value > omp_out.value ? omp_in : omp_out) \
        initializer(omp_priv = omp_orig)

void parallel_selection_sort(long long int* arr, int n) {
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

/**
 * @brief Parallelized linear search
 *
 * @param arr Array to search in
 * @param n Size of the array
 * @param key Element to search for
 */
void parallel_linear_search(long long int* arr, int n, long long int key) {
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            printf(BLUE "[✓] " RESET GREEN "Thread %d found element %lld at index %d\n" RESET,
                   omp_get_thread_num(), key, i + 1);
}

/**
 * @brief Binary search in a chunk of the array
 *
 * @param arr Array to search in
 * @param key Element to search for
 * @param start Start index of the chunk
 * @param end End index of the chunk
 *
 * @return int Index of the element, if found, -1 otherwise
 */
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

/**
 * @brief Parallelized binary search
 *
 * @param arr Array to search in
 * @param key Element to search for
 * @param size Size of the array
 */
void parallel_binary_search(long long int* arr, long long int key, int size) {
#pragma omp parallel shared(arr, key, size)
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int chunk_size = size / num_threads;
        int start = id * chunk_size;
        int end = (id == num_threads - 1) ? size - 1 : start + chunk_size - 1;
        int index = binary_search_chunk(arr, key, start, end);
        // Process the last chunk, if any
        if (id == 0 && size % num_threads != 0) {
            start = size - (size % num_threads);
            end = size - 1;
            index = binary_search_chunk(arr, key, start, end);
        }
        if (index != -1)
            printf(BLUE "[✓] " RESET GREEN "Thread %d found element %lld at index %d\n" RESET, id,
                   key, index + 1);
    }
}

int main() {
    int n = 0;
    double time_1 = 0, time_2 = 0;
    long long int key = 0;

    printf(BLUE "[-] " RESET YELLOW "Enter number of elements in the array: " RESET);
    scanf("%d", &n);

    // Prepare the array using malloc
    long long int* arr = (long long int*)malloc(n * sizeof(long long int));
    printf(BLUE "[-] " RESET YELLOW "Enter the elements of the array: " RESET);
    for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);

    // Run the selection sort algorithm and time it
    time_1 = omp_get_wtime();
    parallel_selection_sort(arr, n);
    time_2 = omp_get_wtime();

    printf(BLUE "[✓] " RESET GREEN "Sorted array: " RESET);
    for (int i = 0; i < n; i++) printf("%lld ", arr[i]);
    printf("\n");

    printf(BLUE "[✓] " RESET GREEN "Time taken: %g\n" RESET, time_2 - time_1);

    printf("\n");

    // Run the linear search algorithm and time it
    printf(BLUE "[!] " RESET YELLOW "Linear Search\n" RESET);
    printf(BLUE "[-] " RESET YELLOW "Enter the element to search for: " RESET);
    scanf("%lld", &key);

    time_1 = omp_get_wtime();
    parallel_linear_search(arr, n, key);
    time_2 = omp_get_wtime();

    printf(BLUE "[✓] " RESET GREEN "Time taken: %g\n" RESET, time_2 - time_1);

    printf("\n");

    // Run the binary search algorithm and time it
    printf(BLUE "[!] " RESET YELLOW "Binary Search\n" RESET);
    printf(BLUE "[-] " RESET YELLOW "Enter the element to search for: " RESET);
    scanf("%lld", &key);

    time_1 = omp_get_wtime();
    parallel_binary_search(arr, key, n);
    time_2 = omp_get_wtime();

    printf(BLUE "[✓] " RESET GREEN "Time taken: %g\n" RESET, time_2 - time_1);

    // Free the array
    free(arr);
}