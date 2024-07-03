# 基本线性代数BLAS算法函数LEVEL2

[toc]

## 预处理的枚举变量

```
CblasNoTrans 	不动
CblasTrans		转置
CblasConjTrans  复数矩阵转置
CblasUpper		上三角
CblasLower		下三角
CblasUnit		对角元素单位化
CblasNoneUnit	对角元素无需单位化
```



```

```



## 程序准备

所有参与运算的方法都会写入  // calc下的空间 

```C
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

int blas_2_test()
{
    int size = 3;
    int i, j, k;
    gsl_vector *X = gsl_vector_alloc(size);
    gsl_vector *Y = gsl_vector_alloc(size);
    gsl_matrix *A = gsl_matrix_alloc(size, size);
    gsl_vector_complex *Xc = gsl_vector_complex_alloc(size);
    gsl_vector_complex *Yc = gsl_vector_complex_alloc(size);
    gsl_matrix_complex *Ac = gsl_matrix_complex_alloc(size, size);
    // 赋初值
    for (i = 0; i < size; i++)
    {
        gsl_vector_set(X, i, i + 1);
        gsl_vector_set(Y, i, i);
        gsl_vector_complex_set(Xc, i, gsl_complex_rect(i + 1, i + 2));
        gsl_vector_complex_set(Yc, i, gsl_complex_rect(i - 1, i - 2));
        for (j = 0; j < size; j++)
        {
            gsl_matrix_set(A, i, j, i + j - 1);
            gsl_matrix_complex_set(Ac, i, j, gsl_complex_rect(i + j - 1, 0));
        }
    }

    //-----------------------
    // calc

    //-----------------------

    // print
    for (i = 0; i < size; i++)
    {
        printf("%f", gsl_vector_get(X, i));
    }
    printf("X\n\n");

    for (i = 0; i < size; i++)
    {
        printf("%f ", gsl_vector_get(Y, i));
    }
    printf("Y\n\n");

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%f ", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }
    printf("A\n\n");

    for (i = 0; i < size; i++)
    {
        printf("%f + %f i",
               GSL_REAL(gsl_vector_complex_get(Xc, i)),
               GSL_IMAG(gsl_vector_complex_get(Xc, i)));
    }
    printf("Xc\n\n");

    for (i = 0; i < size; i++)
    {
        printf("%f + %f i",
               GSL_REAL(gsl_vector_complex_get(Yc, i)),
               GSL_IMAG(gsl_vector_complex_get(Yc, i)));
    }
    printf("Yc\n\n");

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%f + %f i",
                   GSL_REAL(gsl_matrix_complex_get(Ac, i, j)),
                   GSL_IMAG(gsl_matrix_complex_get(Ac, i, j)));
        }
        printf("\n");
    }
    printf("A\n\n");
}
```



## 矩阵与向量的普通运算

```c
// Y=1.0*A*X+0.0*Y
gsl_blas_dgemv(CblasTrans, 1.0, A, X, 0.0, Y); 
//结果存在向量Y中

```

## 包含矩阵操作的函数

```c

// X=upper(A)*X
gsl_blas_dtrmv(CblasUpper, CblasNoTrans, CblasNonUnit, A, X);
// X=inv(upper(A))*X   这是求AX=b的方法
gsl_blas_dtrsv(CblasUpper, CblasNoTrans, CblasNonUnit, A, X);

```

## 矩阵的三角矩阵运算

```c
gsl_blas_dsymv(CblasUpper, 1.0, A, X, 0.0, Y); // Y=1.0*A*X+0.0*Y
gsl_blas_zhemv(CblasUpper, GSL_COMPLEX_ONE, Ac, Xc, GSL_COMPLEX_ZERO, Yc); // 上面函数的复数形式 

//GSL_COMPLEX_ONE=1+0*i
//GSL_COMPLEX_ZERO=0
```

## 矩阵的秩相关函数

```c
gsl_blas_dger(1.0, X, Y, A);              // A=1.0*X*Y^T+A 用于更新矩阵
gsl_blas_dsyr(CblasUpper, 1.0, X, A);     // A=1.0*X*X^T+A
gsl_blas_dsyr2(CblasUpper, 1.0, X, Y, A); // A=1.0*X*Y^T+1.0*Y*X^T+A
```

 