#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define MAXGENE 300000000

typedef struct
{
    float a;
    float b;
} Args;

float *func1(float a, float b)
{
    int i;
    float *result;
    result = (float *)malloc(sizeof(float) * 2);
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
    for (i = 0; i < MAXGENE; i++) // 因为某种不知名的原因，我们必须循环100亿次这个运算
    {
        result[0] = a * b + i / MAXGENE;
        result[1] = a / b + i / MAXGENE;
    }
    return result;
}

void *thread_func1(void *arg)
{
    Args *args = (Args *)arg;
    return func1(args->a, args->b);
}

void *thread_func2(void *arg)
{
    Args *args = (Args *)arg;
    return func2(args->a, args->b);
}

int pthread_test()
{
    float a = 1.2;
    float b = 2.5;

    Args ab;
    ab.a = a;
    ab.b = b;

    float *result1, *result2;

    void *r1, *r2;

    result1 = (float *)malloc(sizeof(float) * 2);
    result2 = (float *)malloc(sizeof(float) * 2);

    pthread_t tid1, tid2;

    struct timeval start, end;
    float during; // 计时参数

    gettimeofday(&start, NULL);

    // 线程变量句柄   线程的属性  执行的函数名称  传入函数的参数（只有一个 放在结构体里）
    pthread_create(&tid1, NULL, thread_func1, &ab);
    pthread_create(&tid2, NULL, thread_func2, &ab);

    // 数据读出
    // 线程变量句柄   保存返回值
    pthread_join(tid1, &r1);
    pthread_join(tid2, &r2);

    result1 = (float *)r1;
    result2 = (float *)r2;

    gettimeofday(&end, NULL);
    
    //退出线程保护资源
    pthread_exit(&tid1);
    pthread_exit(&tid2);

    during = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("result1[0]=%f,result1[1]=%f\n", result1[0], result1[1]);
    printf("result2[0]=%f,result2[1]=%f\n", result2[0], result2[1]);
    printf("during time=%f\n", during);

    return 0;
}
