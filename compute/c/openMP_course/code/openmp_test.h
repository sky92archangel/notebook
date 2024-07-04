#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <omp.h>

int openmp_test()
{
    int i, j, k;
    for (int i = 0; i < 100; i++)
    {
        printf("hello omp i=%d\n", i);
    }

    return 0;
}

int openmp_test_omp()
{
    int i, j, k;

//预处理 openmp   4个并行线程做for
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < 100; i++)
    {
        printf("hello omp i=%d\n", i);
    }

    return 0;
}