#include "openmp_test.h"
#include "openmp_test_section.h"
#include "openmp_test_memory.h"

// gcc main.c -fopenmp
//

int main(void)
{
    openmp_test();
    printf("=============================\n");
    openmp_test_omp();
    printf("=============================\n");
    openmp_test_section();
    printf("=============================\n");
    openmp_test_memory();

    return 0;
}