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
    a1 = gsl_log1p(1);			//ln(1+x) 	x接近0时精度高
    a2 = gsl_expm1(1);			//exp(x)-1
    a3 = gsl_hypot(3, 4);		//sqrt(x*x+y*y)
    a4 = gsl_hypot3(1, 2, 3);	//sqrt(x*x+y*y+z*z)
    a5 = gsl_acosh(1);		
    a6 = gsl_asinh(1);
    a7 = gsl_atanh(0.5);
    a8 = gsl_ldexp(1, 2);		//x*2^n    1*2^2
    a9 = gsl_frexp(4.3, &b);	//	a9=4.3*2^b	  0.5<=x<1

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



```c
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



### 指数

```c
#include <stdio.h> 
#include <gsl/gsl_math.h>

int pow_test(void){ 
    double a1 = gsl_pow_int(1.3,2);
    printf("gsl_pow_int(1.3,2)= %f\n", a1); 
}
```

如果指数为小数，则C语言自带的math库就可以计算；

### 宏函数

#### 符号与奇偶

```c
#include <stdio.h> 
#include <gsl/gsl_math.h>

int sign_test(void)
{ 
    int a = GSL_SIGN(-3);
    int is_odd = GSL_IS_ODD(3);
    int is_even = GSL_IS_EVEN(3);

    printf("GSL_SIGN(-3)= %d\n", a);
    printf("GSL_IS_ODD(3)= %d\n", is_odd);
    printf("GSL_IS_EVEN(3)= %d\n", is_even);
}
```

#### 最值函数

```c
#include <stdio.h> 
#include <gsl/gsl_math.h>

int max_min_test(void)
{
	//纯粹大小
    double a = 21, b = 23;
    int a1 = GSL_MAX(a, b);
    printf("a1= %f\n", a1);
	
    //模糊比较控制精度
    double x = 1.2, y = 1.25;
    double epsilon1 = 0.1;	//精度0.1 大于两者差0.05  比较是合格的
    double epsilon2 = 0.01;	//精度0.01小于两者差0.05  非合格
    int result1 = gsl_fcmp(x, y, epsilon1);
    int result2 = gsl_fcmp(x, y, epsilon2);
    int result3 = gsl_fcmp(y, x, epsilon2);

    printf("%d\n", result1);//0
    printf("%d\n", result2);//-1	x<y  左值小
    printf("%d\n", result3);//1		y>x	 右值小
}
```

#### 常数宏

```c
M_E:自然对数的底数，即e的值(约等于 2.71828)
M_LOG2E:以2为底e的对数(约等于 1.44270)
M LOG10E:以10为底e的对数(约等于0.43429)
M SQRT2:2的平方根(约等于 1.41421)
M_SQRT1_2:1/2 的平方根(约等于 0.70711)
M_SQRT3:3的平方根(约等于1.73205)
M_PI:圆周率，即π的值(约等于 3.14159)
M_PI_2:π/2 的值(约等于 1.57080)
M_PI_4:T/4 的值(约等于 0.78540)
M SQRTPI:π的平方根(约等于1.77245)
M_2_SORTPI:2/的平方根(约等于 1.12838)
M_1_PI:1/π的值(约等于 0.31831)
M_2_PI:2/ 的值(约等于 0.63662)
MLN10:以e为底 10 的对数(约等于 2.30259)
M_LN2:以e为底2的对数(约等于 0.69315)
M LNPI:以e为底π的对数(约等于1.14473)
M_EULER:欧拉常数(约等于 0.57722)
```

















