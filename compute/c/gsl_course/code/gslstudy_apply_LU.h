
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
    // 计算得到的下载矩阵L的对角线为1 ，所以LU的数据都将保存在A中

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