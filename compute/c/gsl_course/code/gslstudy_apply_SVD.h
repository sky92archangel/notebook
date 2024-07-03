
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