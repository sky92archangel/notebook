#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define MAXGENE 300000000

float *func1(float a, float b)
{
    int i;
    float *result;
    result = (float *)malloc(sizeof(float) * 2);
    // #pragma omp parallel for num_threads(4)
    for (i = 0; i < MAXGENE; i++) // 因为某种不知名的原因，我们必须循环100亿次这个运算
    {
        result[0] = a + b + i / MAXGENE;
        result[1] = a - b + i / MAXGENE;
    }
    return result;
}

float *func2(float a, float b)
{
    int i;
    float *result;
    result = (float *)malloc(sizeof(float) * 2);
    // #pragma omp parallel for num_threads(4)
    for (i = 0; i < MAXGENE; i++) // 因为某种不知名的原因，我们必须循环100亿次这个运算
    {
        result[0] = a * b + i / MAXGENE;
        result[1] = a / b + i / MAXGENE;
    }
    return result;
}

int openmp_test_section()
{
    float a = 1.2;
    float b = 2.5;

    float *result1, *result2;
    result1 = (float *)malloc(sizeof(float) * 2);
    result2 = (float *)malloc(sizeof(float) * 2);

    struct timeval start, end;
    float during; // 计时参数

    gettimeofday(&start, NULL);
    
#pragma omp parallel sections
    {
#pragma omp section
        {
            result1 = func1(a, b);
        }
#pragma omp section
        {
            result2 = func2(a, b);
        }
    }

    gettimeofday(&end, NULL);

    during = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("result1[0]=%f,result1[1]=%f\n", result1[0], result1[1]);
    printf("result2[0]=%f,result2[1]=%f\n", result2[0], result2[1]);
    printf("during time=%f\n", during);

    return 0;
}
