# 基本函数

[TOC]



## 常规数学函数

```c
#include <stdio.h> 
#include <gsl/gsl_math.h>

int math_test(void)
{ 
    float a1, a2, a3, a4, a5, a6, a7, a8, a9;
    int b;
    a1 = gsl_log1p(1);
    a2 = gsl_expm1(1);
    a3 = gsl_hypot(3, 4);
    a4 = gsl_hypot3(1, 2, 3);
    a5 = gsl_acosh(1);
    a6 = gsl_asinh(1);
    a7 = gsl_atanh(0.5);
    a8 = gsl_ldexp(1, 2);
    a9 = gsl_frexp(4.3, &b);

    printf("gsl_log1p(1)= %f\n", a1);
    printf("gsl_expm1(1)= %f\n", a2);
    printf("gsl_hypot(3,4)= %f\n", a3);
    printf("gsl_hypot3(1,2,3)= %f\n", a4);
    printf("gsl_acosh(1)= %f\n", a5);
    printf("gsl_asinh(1)= %f\n", a6);
    printf("gsl_atanh(0.5)= %f\n", a7);
    printf("gsl_ldexp(1,2)= %f\n", a8);
    printf("gsl_frexp(1,b)= %f, b=%d\n", a9, b);

    return 0;
}
```



```
gsl_log1p(1)= 0.693147
gsl_expm1(1)= 1.718282
gsl_hypot(3,4)= 5.000000
gsl_hypot3(1,2,3)= 3.741657
gsl_acosh(1)= 0.000000
gsl_asinh(1)= 0.881374
gsl_atanh(0.5)= 0.549306
gsl_ldexp(1,2)= 4.000000
gsl_frexp(1,b)= 0.537500, b=3
```







