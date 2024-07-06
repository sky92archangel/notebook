

# 复数

[TOC]



## 定义

C11中提供了复数的类型，GSL的复数则是另一实现；

### gsl传统定义方法

```c
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_define_test(void){
    gsl_complex a,b;

    GSL_REAL(a)=1.0;
    GSL_IMAG(a)=2.0; //A=1+2i

    GSL_SET_COMPLEX(&b,3.0,4.0);//b=3+4i
  
    printf("a=%f+%fi\n",GSL_REAL(a),GSL_IMAG(a));
    printf("b=%f+%fi\n",GSL_REAL(b),GSL_IMAG(b));

}
```

### C11中的方法

```c
#include <stdio.h>
#include <complex>

int complex_define_c11_test(void){
     complex double a;
     a=1.0+2.0*I;
     printf("a=%f+%fi\n",creal(a),cimag(a));

}
```

### 直角坐标和极坐标定义方法

```c
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_define_test()
{
    gsl_complex a, b;

    a = gsl_complex_rect(1.0, 2.0);
    b = gsl_complex_rect(2.0, 0.5);

    printf("a=%f+%fi\n", GSL_REAL(a), GSL_IMAG(a));
    printf("b=%f+%fi\n", GSL_REAL(b), GSL_IMAG(b));
}
```

## 复数函数方法

### 属性函数

```c
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_prop_test()
{
    gsl_complex a, b;
    a = gsl_complex_rect(1.0, 2.0); // 直角坐标
    
    double arg, abs, abs2, logabs;
    
    arg = gsl_complex_arg(a); // 相位
    abs = gsl_complex_abs(a);//模
    abs2 = gsl_complex_abs2(a);//模的平方
    logabs = gsl_complex_logabs(a);//模的对数 ln(sqrt(x*x+y*y))
    
    printf("arg(a)= &f\n", arg);
    printf("abs(a)= %f\n", abs);
    printf("abs2(a)= &f\n", abs2);
    printf("logabs(a)= &f\n", logabs);
    
    return 0;
}
```

### 运算函数

```c
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_calc_test()
{
    gsl_complex a = gsl_complex_rect(1.0, 2.0);
    gsl_complex b = gsl_complex_rect(3.0, 4.0);

    double c = 2.0;

    gsl_complex r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;
    
    r1 = gsl_complex_add(a, b);			//复数和
    r2 = gsl_complex_add_real(a, c);	//a的实部加实数c 
    r3 = gsl_complex_add_imag(a, c);	//a的虚部加实数c 
    r4 = gsl_complex_sub(a, b);			//复数差
    r5 = gsl_complex_sub_real(a, c);	//a的实部减实数c
    r6 = gsl_complex_sub_imag(a, c);	//a的虚部减实数c 
    r7 = gsl_complex_mul(a, b);			//复数积
    r8 = gsl_complex_mul_real(a, c);	//a的实部乘实数c
    r9 = gsl_complex_mul_imag(a, c);	//a的虚部乘实数c
    r10 = gsl_complex_div(a, b);		//复数除法
    r11 = gsl_complex_div_real(a, c);	//a的实部除实数c
    r12 = gsl_complex_div_imag(a, c);	//a的虚部除实数c
    r13 = gsl_complex_conjugate(a);		//a的共轭
    r14 = gsl_complex_inverse(a);		//a的逆     共轭/(模^2)
    r15 = gsl_complex_negative(a);		//a的全负
    
    return 0;
}

```

### 幂运算

```c
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_pow_test()
{
    gsl_complex a = gsl_complex_rect(1.0, 2.0);
    gsl_complex b = gsl_complex_rect(3.0, 4.0);
    
    double c = 2.0;
    gsl_complex r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;
    
    r1 = gsl_complex_sqrt(a);			//开根
    r2 = gsl_complex_sqrt_real(c);		//实数的开根
    r3 = gsl_complex_pow(a, b);			//a^b
    r4 = gsl_complex_pow_real(a, c);	//a^c
    r5 = gsl_complex_exp(a);			//e^a
    r6 = gsl_complex_log(a);			//自然对数   ln a
    r7 = gsl_complex_log10(a);			//10为底对数
    r8 = gsl_complex_log_b(a, b);		//b为底对数
    return 0;
}
```

## 复数三角函数

正三角函数

```C
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_tri_test()
{ 
    gsl_complex a = gsl_complex_rect(1.0, 2.0);
    double b = 2.0;
    gsl_complex r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11;
    // code
    r1 = gsl_complex_sin(a);
    r2 = gsl_complex_cos(a);
    r3 = gsl_complex_tan(a);
    r4 = gsl_complex_sec(a);		//正割  1/cos(a)
    r5 = gsl_complex_csc(a);		//余割  1/sin(a)
    r6 = gsl_complex_cot(a);		//余切  1/tan(a)		
    printf("r1 = %f + &fi\n", GSL_REAL(r1), GSL_IMAG(r1));
    printf("r2 = %f + %fi\n", GSL_REAL(r2), GSL_IMAG(r2));
    printf("r3 = %f + &fi\n", GSL_REAL(r3), GSL_IMAG(r3));
    printf("r4 = %f + &fi\n", GSL_REAL(r4), GSL_IMAG(r4));
    printf("r5 = %f + &fi\n", GSL_REAL(r5), GSL_IMAG(r5));
    printf("r6 = &f + &fi\n", GSL_REAL(r6), GSL_IMAG(r6));
}

```

反三角函数

```C
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_arctri_test()
{
    gsl_complex a = gsl_complex_rect(1.0, 2.0);
    double b = 2.0;
    gsl_complex r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11;
    // code
    r1 = gsl_complex_arcsin(a);
    r2 = gsl_complex_arcsin_real(b);
    r3 = gsl_complex_arccos(a);
    r4 = gsl_complex_arccos_real(b);
    r5 = gsl_complex_arctan(a);
    r6 = gsl_complex_arcsec(a);
    r7 = gsl_complex_arcsec_real(b);
    r8 = gsl_complex_arccsc(a);
    r9 = gsl_complex_arccsc_real(b);
    r10 = gsl_complex_arccot(a);

    printf("r1=%f+%fi\n", GSL_REAL(r1), GSL_IMAG(r1));
    printf("r2=%f+%fi\n", GSL_REAL(r2), GSL_IMAG(r2));
    printf("r3=%f+%fi\n", GSL_REAL(r3), GSL_IMAG(r3));
    printf("r4=%f+%fi\n", GSL_REAL(r4), GSL_IMAG(r4));
    printf("r5=%f+%fi\n", GSL_REAL(r5), GSL_IMAG(r5));
    printf("r6=%f+%fi\n", GSL_REAL(r6), GSL_IMAG(r6));
    printf("r7=%f+%fi\n", GSL_REAL(r7), GSL_IMAG(r7));
    printf("r8=%f+%fi\n", GSL_REAL(r8), GSL_IMAG(r8));
    printf("r9=%f+%fi\n", GSL_REAL(r9), GSL_IMAG(r9));
    printf("r10=%f+%fi\n", GSL_REAL(r10), GSL_IMAG(r10));
    
    return 0;
}

```



双曲函数

```C
#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int complex_hyperbolic_test()
{
    gsl_complex a = gsl_complex_rect(1.0, 2.0);
    double b = 1.0;
    gsl_complex r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11;
    // code
    r1 = gsl_complex_sinh(a);
    r2 = gsl_complex_cosh(a);
    r3 = gsl_complex_tanh(a);
    r4 = gsl_complex_sech(a);
    r5 = gsl_complex_csch(a);
    r6 = gsl_complex_coth(a);

    printf("r1 = &f + &fi\n", GSL_REAL(r1), GSL_IMAG(r1));
    printf("r2 = %f + &fi\n", GSL_REAL(r2), GSL_IMAG(r2));
    printf("r3 = %f + &fi\n", GSL_REAL(r3), GSL_IMAG(r3));
    printf("r4 = &f + &fi\n", GSL_REAL(r4), GSL_IMAG(r4));
    printf("r5 = &f + &fi\n", GSL_REAL(r5), GSL_IMAG(r5));
    printf("r6 = %f + &fi\n", GSL_REAL(r6), GSL_IMAG(r6));
}
```

