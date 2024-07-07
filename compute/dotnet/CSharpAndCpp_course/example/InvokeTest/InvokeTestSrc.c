#include <stdio.h>

//gcc -shared -fPIC  InvokeTestSrc.c -o libtest.dll

int HelloC()
{
    printf("hello");
    return 0;
}

int SumC(int a, int b)
{
    return a + b;
}