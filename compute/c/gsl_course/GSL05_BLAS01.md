# 基本线性代数BLAS算法函数LEVEL1





## BLAS简介

BALS : basic linear algebra subprograms 基本线代子程序集

最初为netlib组织使用fortran写的接口

该接口的标准发展为了openBLAS，MKL，cBLAS，GSL等线代库，其函数形式大致相同；

类似matlab，tensorflow的底层都使用BLAS的接口标准

GSL中也提供了cBLAS，虽然性能不是最强的；



BLAS分为三各层级

第一层级：向量*向量

第二层级：向量*矩阵

第三层级：矩阵*矩阵



## BLAS函数命名

变量数据类型在C语言中必须完全对应    int 和 unsigned long 也有区别；

BLAS中各种函数名关键字符

| 函数名关键字 | 对应数据类型                 |      |
| ------------ | ---------------------------- | ---- |
| S            | 单精度float                  |      |
| D            | 双精度double                 |      |
| C            | 单精度复数 gsl_complex_float |      |
| Z            | 双精度复数 gsl_complex       |      |

例子：两个向量的点积

```c
//全部为单精度计算 故只有s这个关键字
int gsl_blas_sdot(const gsl_vector_float* x, const gsl_vector_float* y, float* result)
//显然输入单精度，结果为双精度  故有ds两个关键字
int gsl_blas_dsdot(const gsl_vector_float* x, const gsl_vector_float* y, double* result)
```

 

## 向量点乘

```c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

// level 1
int blas_dot_test()
{
    int i, j, k;

    gsl_vector *v = gsl_vector_alloc(3);
    gsl_vector *w = gsl_vector_alloc(3);
    double *result = (double *)malloc(sizeof(double));

    gsl_vector_complex *v_complex = gsl_vector_complex_alloc(3);
    gsl_vector_complex *w_complex = gsl_vector_complex_alloc(3);
    gsl_complex *result_complex = (gsl_complex *)malloc(sizeof(gsl_complex));
  
    for (i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 2 * i); // 0 2 4
        gsl_vector_set(w, i, 4 + i); // 4 5 6
        gsl_vector_complex_set(v_complex, i, gsl_complex_rect(i, i));
        gsl_vector_complex_set(w_complex, i, gsl_complex_rect(i, i));
    }

    // 点积
    gsl_blas_ddot(v, w, result); // v'*w v1*w1+V2*w2+v3*w3
    // 复数点积
    gsl_blas_zdotu(v_complex, w_complex, result_complex); // v'*w
    // 复数点积w_complex会进行共轭处理
    gsl_blas_zdotc(v_complex, w_complex, result_complex); // w_complex会进行共轭处理

    printf("The result is: %f\n", *result);
    printf("The complex result is: %f + %f i\n", GSL_REAL(*result_complex), GSL_IMAG(*result_complex));

    return 0;
}
```



## 向量范数

```c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int blas_norm_test()
{
    int i, j, k;

    gsl_vector *v = gsl_vector_alloc(3);
    gsl_vector *w = gsl_vector_alloc(3);
    double *result = (double *)malloc(sizeof(double));

    gsl_vector_complex *v_complex = gsl_vector_complex_alloc(3);
    gsl_vector_complex *w_complex = gsl_vector_complex_alloc(3);
    gsl_complex *result_complex = (gsl_complex *)malloc(sizeof(gsl_complex));

    for (i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 2 * i); // 0 2 4
        gsl_vector_set(w, i, 4 + i); // 4 5 6
        gsl_vector_complex_set(v_complex, i, gsl_complex_rect(i, i));
        gsl_vector_complex_set(w_complex, i, gsl_complex_rect(i, i));
    }

    *result = gsl_blas_dnrm2(v);          // 计算向量的2范数
    *result = gsl_blas_dznrm2(v_complex); // 计算复数向量的2 范数
    printf("The result is: &f\n", *result);

    return 0;
}
```



## 向量求和以及检索

```c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int blas_index_test()
{
    int i, j, k;

    gsl_vector *v = gsl_vector_alloc(3);
    gsl_vector *w = gsl_vector_alloc(3);
    double *result = (double *)malloc(sizeof(double));

    gsl_vector_complex *v_complex = gsl_vector_complex_alloc(3);
    gsl_vector_complex *w_complex = gsl_vector_complex_alloc(3);
    gsl_complex *result_complex = (gsl_complex *)malloc(sizeof(gsl_complex));

    for (i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 2 * i); // 0 2 4
        gsl_vector_set(w, i, 4 + i); // 4 5 6
        gsl_vector_complex_set(v_complex, i, gsl_complex_rect(i, i));
        gsl_vector_complex_set(w_complex, i, gsl_complex_rect(i, i));
    }

    //--------------------
    *result = gsl_blas_dasum(v);                       // 计算向量v中元素之和
    *result = gsl_blas_dzasum(v_complex);              // 计算复数向量v中的元素之和
    size_t n_max = gsl_blas_idamax(v);                 // 找到向量v中最大元素的角标
    size_t n_max_complex = gsl_blas_izamax(v_complex); // 找到复数向量v中最大元素的角标  模的最大者索引
    printf("The result is: &f\n", *result);
    printf("The id is: &d\n", n_max);
    //--------------------

    return 0;
}

```

## 向量的计算和操作

```c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int blas_calc_test()
{
    int i, j, k;

    gsl_vector *v = gsl_vector_alloc(3);
    gsl_vector *w = gsl_vector_alloc(3);
    double *result = (double *)malloc(sizeof(double));

    gsl_vector_complex *v_complex = gsl_vector_complex_alloc(3);
    gsl_vector_complex *w_complex = gsl_vector_complex_alloc(3);
    gsl_complex *result_complex = (gsl_complex *)malloc(sizeof(gsl_complex));

    for (i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 2 * i); // 0 2 4
        gsl_vector_set(w, i, 4 + i); // 4 5 6
        gsl_vector_complex_set(v_complex, i, gsl_complex_rect(i, i));
        gsl_vector_complex_set(w_complex, i, gsl_complex_rect(i, i));
    }

    //--------------------

    gsl_blas_dswap(v, w);       // 交换v和w向量的内容
    gsl_blas_zswap(v_complex, w_complex);
    gsl_blas_dcopy(v, w);       // 将v复制到w中
    gsl_blas_zcopy(v_complex, w_complex);

    gsl_blas_daxpy(4.0, v, w);  // w=v*4+w
    gsl_blas_zaxpy(gsl_complex_rect(1, 2), v_complex, w_complex); //v_complex*(1+2i)+w_complex
    gsl_blas_dscal(4.0, v);     // v=v*4;
    gsl_blas_zscal(gsl_complex_rect(1, 2), v_complex);  //v_complex*(1+2i)

    gsl_blas_zdscal(4.0, v_complex);    //v_complex*4.0

    //--------------------

    return 0;
}
```

## 向量的旋转变化 吉文斯变换

初等旋转变换，用于正则化向量，使其某分量为0，用于QR分解，奇异值分解；

```c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int blas_rot_test()
{
    int i, j, k;

    gsl_vector *v = gsl_vector_alloc(3);
    gsl_vector *w = gsl_vector_alloc(3);

    for (i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 2 * i); // 0 2 4
        gsl_vector_set(w, i, 4 + i); // 4 5 6
    }

    //--------------------
    double a = 1, b = 2, c, s, P;
    gsl_blas_drotg(&a, &b, &c, &s);
    gsl_blas_drot(v, w, c, s);
    gsl_blas_drotmg(&a, &b, &c, s, &P);
    gsl_blas_drotm(v, w, &P); // 改进的吉文斯变换
    //--------------------

    return 0;
}

```

## 单精度BLAS的level1函数

```c
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 


int bals_level1_test()
{
    // 单精度level 1函数 点乘函数
    int gsl_blas_sdot(const gsl_vector_float *x, const gsl_vector_float *y, float *result);
    int gsl_blas_dsdot(const gsl_vector_float *x, const gsl_vector_float *y, double *result);
    int gsl_blas_cdotc(const gsl_vector_complex_float *x, const gsl_vector_complex, float *y, gsl_complex_float *dotc);
    int gsl_blas_cdotu(const gsl_vector_complex_float *x, const gsl_vector_complex, float *y, gsl_complex_float *dotu);

    // 单精度level 1函数--范数与求和
    float gsl_blas_snrm2(const gsl_vector_float *x);
    float gsl_blas_scnrm2(const gsl_vector_complex_float *x);
    float gsl_blas_sasum(const gsl_vector_float *x);
    float gsl_blas_scasum(const gsl_vector_complex_float *x);

    // 单精度level 1函数--向量操作
    int gsl_blas_sswap(gsl_vector_float * x, gsl_vector_float * y);
    int gsl_blas_cswap(gsl_vector_complex_float * x, gsl_vector_complex_float * y);
    int gsl_blas_scopy(const gsl_vector_float *x, gsl_vector_float *y);
    int gsl_blas_ccopy(const gsl_vector_complex_float *x, gsl_vector_complex_float *y);

    // 单精度level 1函数--向量操作
    int gsl_blas_saxpy(float alpha, const gsl_vector_float *x, gsl_vector_float *y);
    int gsl_blas_caxpy(const gsl_complex_float alpha, const gsl_vector_complex_float *x, gsl_vector_complex_float *y);
    void gsl_blas_cscal(const gsl_complex_float alpha, gsl_vector_complex_float *x);
    void gsl_blas_csscal(float alpha, gsl_vector_complex_float *x);

    // 单精度level 1函数--初等旋转变换
    int gsl_blas_srotg(float all, float bll, float cll, float sl);
    int gsl_blas_srot(gsl_vector_float * x, gsl_vector_float * y, float c, float s);
    int gsl_blas_srotmg(float d1l, float d2l, float b1l, float b2, float Pl);
    int gsl_blas_srotm(gsl_vector_float * x, gsl_vector_float * y, const float Pl);
}


```

