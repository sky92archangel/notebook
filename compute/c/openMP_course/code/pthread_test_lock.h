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