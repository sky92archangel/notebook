# 应用

[TOC]

## LU分解 解方程

为快速解开 高维度矩阵 （100行列）常将A分解为LU两个矩阵，一个下三角，一个上三角；使得可以快速解；

```c

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>

int apply_lu_test()
{
    int i, j;
    gsl_matrix *A = gsl_matrix_alloc(3, 3);
    gsl_vector *b = gsl_vector_alloc(3);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            gsl_matrix_set(A, i, j, i + j + 1);
        gsl_vector_set(b, i, i + 1);
    } // 矩阵向量初始化

    // A
    // 1 2 3
    // 2 3 4
    // 3 4 5

    // b=(1,2,3)^T

    // LU
    gsl_permutation *p = gsl_permutation_alloc(3); // 用于存储行交换的信息
    int s;                                         // 用于存储行交换的次数
    gsl_linalg_LU_decomp(A, p, &s);                // 对A进行LU分解，将分解结果存储在A中
    // 计算得到的下载矩阵L的对角线为1 ，所以LU的数据都将重叠的保存在A中

    printf("LU 分解结果:");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%f", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }

    // 解Ax=b
    gsl_vector *x = gsl_vector_alloc(3); // 解存放的地方
    gsl_linalg_LU_solve(A, p, b, x);
    for (i = 0; i < 3; i++)
    {
        printf("x_%d = %g\n", i, gsl_vector_get(x, i));
    }

    gsl_matrix_free(A);
    gsl_vector_free(b);
    gsl_vector_free(x);
    gsl_permutation_free(p);
}
```



## SVD 奇异分解

由于矩阵求逆比较麻烦；

所以试着寻找一个逆矩阵为自身或自身转置；

这个就是酉矩阵，其逆矩阵就是其共轭转置；
$$
U^{-1}=U^\dagger
$$
奇异分解：是将一个矩阵分解为酉矩阵和对角矩阵的方法
$$
A=U\Sigma V^\dagger
\\
U V酉矩阵
\\
\Sigma 对角矩阵
$$
这样就可以快速求A的逆矩阵；



SVD数学部分
$$
(A^\top A)v_i=\lambda_i v_i
求特征向量并构成酉矩阵V
\\
(A A^\top )u_i=\lambda_i u_i
求特征向量并构成酉矩阵U
\\
对角矩阵\Sigma的元素都是A的奇异值，基本都是将矩阵A的特征值开根号得到\\
\Sigma = \begin {bmatrix} 
\sqrt(\lambda_1) 	& 0					& 0 				\\
0					&\sqrt(\lambda_2) 	& 0 				\\
0					&0 					&\sqrt(\lambda_2)   \\
\end{bmatrix}
$$
那么线性方程组就可以这样解
$$
A=U\Sigma V^\dagger,U^{-1}=U^\dagger,V^{-1}=V^\dagger
\\
Ax=b
\\
x=A^{-1}b=(V^\dagger)^{-1}\Sigma^{-1}U^{-1} b =V\Sigma^{-1}U^\dagger b 
\\
x=V\Sigma^{-1}U^\dagger b
$$




## 代码



```C

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>

int apply_svd_test()
{ 
    int i, j;
    gsl_matrix *A = gsl_matrix_alloc(3, 3);
    gsl_matrix *V = gsl_matrix_alloc(3, 3);
    gsl_vector *S = gsl_vector_alloc(3);
    gsl_vector *work = gsl_vector_alloc(3); // 中间计算结果
    gsl_vector *b = gsl_vector_alloc(3);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            gsl_matrix_set(A, i, j, i + j + 1);
        }
        gsl_vector_set(b, i, i + 1);
    } // 矩阵向量的初始化

    // A
    // 1 2 3
    // 2 3 4
    // 3 4 5

    // b=(1,2,3)^T

    // SVD
    gsl_linalg_SV_decomp(A, V, S, work);

    // print SVD 结果
    printf("SVD 结果 酉矩阵 U:\n");

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            printf("%f ", gsl_matrix_get(A, i, j));

        printf("\n");
    }

    //酉矩阵V直接存在矩阵A中 以节省空间
    printf("SVD 结果 酉矩阵 V:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            printf("%f ", gsl_matrix_get(V, i, j));
        printf("\n");
    }

    //对角矩阵 S
    printf("SVD 结果 对角矩阵 S:\n");
    for (i = 0; i < 3; i++)
    {
        printf("%f\n", i, gsl_vector_get(S, i));
    }
    printf("\n");

    // solve Ax=b
    gsl_vector *x = gsl_vector_alloc(3); // 解存放变量内存头
    gsl_linalg_SV_solve(A, V, S, b, x);
    for (i = 0; i < 3; i++)
    {
        printf("x_%d = %g\n", i, gsl_vector_get(x, i));
    }
    gsl_matrix_free(A);
    gsl_matrix_free(V);
    gsl_vector_free(b);
    gsl_vector_free(x);
    gsl_vector_free(S);
    gsl_vector_free(work);

}
```

 



