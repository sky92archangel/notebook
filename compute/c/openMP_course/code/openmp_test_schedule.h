
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