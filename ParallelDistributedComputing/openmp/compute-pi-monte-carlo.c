/**
 * @file compute-pi-monte-carlo.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Compute pi using the Monte Carlo method, and run it in parallel using OpenMP
 * @date 2023-02-01
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "omp.h"
#include "../include/terminal.h"

/**
 * @brief Compute pi using the Monte Carlo method
 *
 * @param n Number of points to generate
 */
double compute_pi(int n, int threads) {
    // Store X and Y coordinates of the points
    double x = 0, y = 0;

    // Store the distance of a random point
    // from the origin
    double distance = 0;

    // Store number of points inside the circle
    int points_inside_circle = 0;

    // Store number of points lying inside the square
    int points_inside_square = 0;

    int i = 0;

#pragma omp parallel firstprivate(x, y, distance, i) num_threads(threads) reduction(+ \
                                                                               : points_inside_circle, points_inside_square)
    {
        // Initialize random points with a seed

        srand48((int) time(NULL) + omp_get_thread_num());

#pragma omp for
        for (i = 0; i < n; i++) {
            // Generate random points
            x = (double) rand() / (double) RAND_MAX;
            y = (double) rand() / (double) RAND_MAX;

            // Calculate distance of a point from the origin
            distance = (x * x) + (y * y);

            // Check if the point lies inside the circle
            if (distance <= 1) {
                points_inside_circle++;
            }

            // Increment the number of points inside the square
            points_inside_square++;
        }
    }

    // Stores the estimated value of pi
    double pi = 4.0 * ((double) points_inside_circle / (double) (points_inside_square));

    return pi;
}

int main() {
    // Number of points to generate
    int n = 0;

    // Number of threads to use
    int threads = omp_get_max_threads();

    // Get the number of points to generate
    printf(BLUE "[-]" RESET RED " Enter the number of points to generate: " RESET);
    scanf("%d", &n);

    // Time the execution of the Monte Carlo method
    double start = omp_get_wtime();

    // Run the Monte Carlo method
    double pi = compute_pi(n, threads);

    // Time the execution of the Monte Carlo method
    double end = omp_get_wtime();

    // Print the estimated value of pi
    printf(BLUE "[-] " RESET GREEN "Estimated value of pi: %f\n" RESET, pi);

    // Print the time taken to compute pi
    printf(BLUE "[-] " RESET GREEN "Time taken to compute pi: %f seconds\n" RESET, end - start);

    return 0;
}