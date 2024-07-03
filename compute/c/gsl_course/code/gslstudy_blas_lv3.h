#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_blas.h>
// #include <gsl/gsl_vector.h>
// #include <gsl/gsl_complex.h>
// #include <gsl/gsl_complex_math.h>

int blas_3_test()
{
    int size = 3; // 所有的矩阵都是3x3的
    int i, j, ks;
    gsl_matrix *A = gsl_matrix_alloc(size, size);
    gsl_matrix *B = gsl_matrix_alloc(size, size);
    gsl_matrix *C = gsl_matrix_alloc(size, size);
    // 为矩阵赋初值
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            gsl_matrix_set(A, i, j, i + j + 1);
            gsl_matrix_set(A, i, j, i - j + 2);
            gsl_matrix_set(A, i, j, i * j + 1);
        }
    }
    // 函数
    //-----------------------
    // C=1.0*A*B+0.0*C
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, A, B, 0.0, C);
    // C=1.0*A*B+0.0*C
    gsl_blas_dsymm(CblasLeft, CblasUpper, 1.0, A, B, 0.0, C);

    // C=1.0*B*A+0.0*C
    gsl_blas_dsymm(CblasRight, CblasUpper, 1.0, A, B, 0.0, C);

    // 三角矩阵在左侧  三角矩上三角  三角矩不转置  三角矩不对角单位化  B=1.0*A*B
    gsl_blas_dtrmm(CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, 1.0, A, B);

    // 解决AX=B 或者 XA=B的线性方程组   B=1.0*A*B
    gsl_blas_dtrsm(CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, 1.0, A, B);
    // 用于计算矩阵的秩K 更新  C取上三角 C不转置  C=1.0*A*A^T+0.0*C
    gsl_blas_dsyrk(CblasUpper, CblasNoTrans, 1.0, A, 0.0, C);

    // 用于计算矩阵的秩K 更新  C取上三角 C不转置  C=1.0*A*B^T+1.0*B*A^T+0.0*C
    gsl_blas_dsyr2k(CblasUpper, CblasNoTrans, 1.0, A, B, 0.0, C);

    //-----------------------

    // 输出
    printf("A:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%f", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }

    printf("B:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%f", gsl_matrix_get(B, i, j));
        }
        printf("\n");
    }

    printf("C:\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%f", gsl_matrix_get(C, i, j));
        }
        printf("\n");
    }
}