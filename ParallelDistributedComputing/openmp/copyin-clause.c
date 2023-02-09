/**
 * @name copyin-clause.c
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Write an OpenMP program that makes use of the copyin clause.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/terminal.h"
#include "omp.h"

int a = 66739;

#pragma omp threadprivate(a)

/**
 * @brief Illustrates how to use the copyin clause.
 * @details This application declares a global variable and specifies it as
 * threadprivate. This variable is then passed a copyin to the first parallel
 * region. In that region, the master thread modifies its value but other
 * threads will not see the update until the second parallel region; where the
 * variable will be passed as copyin again.
 **/
int main() {
    omp_set_dynamic(0);

#pragma omp parallel copyin(a)
    {
#pragma omp master
        {
            printf(BLUE "[FIRST PARALLEL REGION] " RESET GREEN "Thread %d: a = %d (copyin)\n" RESET,
                   omp_get_thread_num(), a);
            a = 54321;
            printf(BLUE "[FIRST PARALLEL REGION] " RESET GREEN
                        "Thread %d: a = %d (copyin after master thread changes value)\n" RESET,
                   omp_get_thread_num(), a);
        }

#pragma omp barrier
        printf(BLUE "[FIRST PARALLEL REGION] " RESET GREEN "Thread %d: a = %d (copyin)\n" RESET,
               omp_get_thread_num(), a);
    }

#pragma omp parallel copyin(a)
    {
        printf(BLUE "[SECOND PARALLEL REGION] " RESET GREEN "Thread %d: a = %d (copyin)\n" RESET,
               omp_get_thread_num(), a);
    }

    return 0;
}