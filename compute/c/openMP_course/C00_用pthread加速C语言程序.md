# 用pthread加速自己的c语言程序

[TOC]

## 简介

pthread为C语言原生函数库 

## 头文件

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
```

 

## 未加速代码

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define MAXGENE 300000000

float *func1(float a, float b)
{
    int i;
    float *result;
    result = (float *)malloc(sizeof(float) * 2);
    for (i = 0; i < MAXGENE; i++) // 因为某种不知名的原因，我们必须循环100亿次这个运算
    {
        result[0] = a + b+i/MAXGENE;
        result[1] = a - b+i/MAXGENE;
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
        result[0] = a * b+i/MAXGENE;
        result[1] = a / b+i/MAXGENE;
    }
    return result;
}



int pthread_test ()
{
    float a = 1.2;
    float b = 2.5;

    float *result1, *result2;
    result1 = (float *)malloc(sizeof(float) * 2);
    result2 = (float *)malloc(sizeof(float) * 2);

    struct timeval start, end;
    float during; // 计时参数

    gettimeofday(&start, NULL);
    result1 = func1(a, b);
    result2 = func2(a, b);
    gettimeofday(&end, NULL);

    during = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("result1[0]=%f,result1[1]=%f\n", result1[0], result1[1]);
    printf("result2[0]=%f,result2[1]=%f\n", result2[0], result2[1]);
    printf("during time=%f\n", during);

    return 0;
}

```



## 加速代码

```c
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

```





## 关于pthread的锁问题

渔夫和猫

一个鱼篓最多装10条鱼
渔夫捕鱼占用鱼篓
猫吃鱼也占用鱼篓

两者行为并行时
为避免抢占鱼篓变量资源
需要启用线程锁 



```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int countFish = 0; // 计数器，记录容器内鱼的数量
int numFish = 10;  // 一筐鱼的数量

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 初始化一把叫做mutex的锁

pthread_cond_t cond_catchfish_finish = PTHREAD_COND_INITIALIZER;
// 初始化一个条件变量，这个条件变量为捕鱼操作是否完成

pthread_cond_t cond_eatfish_finish = PTHREAD_COND_INITIALIZER;
// 初始化一个条件变量，这个条件变量为吃鱼操作是否完成

void *fishman(void *)
{
    int i, j, k;
    for (i = 0; i < numFish * 2; i++)
    {
        pthread_mutex_lock(&mutex);
        // 渔夫在捕鱼时，先加一把锁，防止猫咪把容器抢走
        while (countFish == numFish)
        {
            pthread_cond_wait(&cond_eatfish_finish, &mutex);
            // 如果容器中鱼满了，渔夫就等待猫咪吃完鱼，然后再继续捕鱼//当没有接收到cond_eatfish_finish信号时，就会一直等待，并且会释放mutex锁
        }
        countFish++;
        // 捕到一条鱼
        printf("Catching Fish! Now there are %d fish, total fish are %d\n", countFish, i + 1);

        pthread_cond_signal(&cond_catchfish_finish);
        // 发送信号，告诉猫可以吃鱼了，但若没有抓够，猫会等，因为锁未解；

        pthread_mutex_unlock(&mutex);
        // 解锁
    }
    pthread_exit(NULL);
}

void *cat(void *)
{
    int i, j, k;
    for (i = 0; i < numFish * 2; i++)
    {
        pthread_mutex_lock(&mutex);
        // 猫咪在吃鱼时，先加一把锁，防止渔夫把容器抢走
        while (countFish == 0)
        {
            pthread_cond_wait(&cond_catchfish_finish, &mutex);
            // 如果容器中鱼没有了，猫咪就等待渔夫捕鱼的操作完成，然后继续吃鱼
            // 当没有接收到cond catchfish finish信号时，就会一直等待，并且会释放mutex锁
        }
        countFish--;
        // 吃掉一只鱼
        printf("Eating Fish! Now there are %d fish\n", countFish);

        pthread_cond_signal(&cond_eatfish_finish);
        // 发送信号 告诉渔夫可以继续捕鱼了 但是没有吃完 渔夫会等 因为没解锁

        pthread_mutex_unlock(&mutex);
        // 解锁
    }
    pthread_exit(NULL);
}

int pthread_test()
{
    printf("START!\n");

    pthread_t fishmanThread, catThread;
    pthread_create(&fishmanThread, NULL, fishman, NULL);
    pthread_create(&catThread, NULL, cat, NULL);

    pthread_join(fishmanThread, NULL);
    pthread_join(catThread, NULL);

    printf("The cat is full!\n");

    
    return 0;
}
```

