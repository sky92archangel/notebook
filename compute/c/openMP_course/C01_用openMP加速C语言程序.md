# 用openMP加速C语言程序

[TOC]

## 主程序

```C
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
```



 

## 简单并行

```C
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
```



## SECTION并行域使用

```c
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

```



## 关于openMP内存抢占问题

openMP基于内存共享做并行 故是线程安全的

```C
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

```



## 调度方式

openMP提供了三种调度方式做线程调度

// static    9=> a1234 b5678 a9  静态分配
// dynamic   9=> a1 b2 a3 b4 a5 a6 a7 b8 a9   完成任务的线程自动寻未启任务
// guided    9=> a1234 b567 c89  依次递减分配



```C

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// static    9=> a1234 b5678 a9  静态分配
// dynamic   9=> a1 b2 a3 b4 a5 a6 a7 b8 a9   完成任务的线程自动寻未启任务
// guided    9=> a1234 b567 c89  依次递减分配

int openmp_test_schedule()
{
    int i, j, k;
    float a = 1.2;
    float b = 2.5;

    float *result = (float *)malloc(sizeof(float) * 10);

#pragma omp parallel for num threads(4) schedule(dynamic, 2)
    // num_threads(4)表示创建4个线程
    // schedule(dynamic,2)表示dynamic调度模式，每个线程执行两个任务
    //  同样也可以:
    // schedule(static,2)schedule(guided,2)
    for (i = 0; i < 10; i++)
    {
        result[i] = i * 2;
        printf("write num from %d\n", omp_get_thread_num());
    }

    
#pragma omp parallel for num threads(4) schedule(dynamic, 2)
    for (i = 0; i < 10; i++)
    {
#pragma omp critical
        {
            result[i] = i * 3;
        } // critical标志这段代码是临界区，同一时间只能有一个线程进入
    }


#pragma omp barrier
    // barrier表示等待所有线程执行完毕，才能继续执行下面的代码，是一个同步点

    return 0;
}
```









