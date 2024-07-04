#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

int openmp_test_memory()
{
    int i, j, k;
    float a = 1.2;
    float b = 2.5;
    float *result;
    result = (float *)malloc(sizeof(float) * 10);
#pragma omp parallel for num_threads(4)
    for (i = 0; i < 10; i++)
    {
        result[i] = i * 2;
        printf("write num from %d\n", omp_get_thread_num());
        // omp_get_thread_num函数用于获取当前执行的线程编号，线程编号是系统默认给出的
    }
    for (i = 0; i < 10; i++)
    {
        printf("%f\n", result[i]);
    }

    return 0;
}
