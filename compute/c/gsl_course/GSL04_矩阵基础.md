# 矩阵基础函数

[TOC]



## 头文件

```C
#include <stdio.h>
#include <gsl/gsl_matrix.h>

```

## 定义

```C
#include <stdio.h>
#include <gsl/gsl_matrix.h>

int matrix_define_test()
{
    // 定义一个3x3的矩阵(注意这里是一个指针)
    gsl_matrix *m = gsl_matrix_alloc(3, 3);

    // 设置矩阵m的(0,0)位置为1.23
    gsl_matrix_set(m, 0, 0, 1.23);
    // 设置矩阵m的(1,2)位置为3.45
    gsl_matrix_set(m, 1, 2, 3.45);

    // 获取(0,0)的值
    printf("m(0,0)=%g\n", gsl_matrix_get(m, 0, 0));
    // 获取(1,2)的值
    printf("m(0,0)=&g\n", gsl_matrix_get(m, 1, 2));

    // 将m所有的元素都设置为0
    gsl_matrix_set_all(m, 0.0);
    // 释放内存
    gsl_matrix_free(m);
}

```

## 切片

```C
#include <stdio.h>
#include <gsl/gsl_matrix.h>

int matrix_slice_test()
{
    gsl_matrix *m = gsl_matrix_alloc(5, 5);
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            gsl_matrix_set(m, i, j, 2 + i + j);

    // sub
    // 矩阵变量,行起点,列起点,行元素数,列元素数
    gsl_matrix_view m_sub = gsl_matrix_submatrix(m, 1, 1, 3, 3);

    // 数组转矩阵 同时切片
    double a[5][5] = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
        {4, 5, 6, 7, 8},
        {5, 6, 7, 8, 9}};
    
    //该函数切二维数组时会直接拿出平铺前九值个放在3*3矩阵中
    gsl_matrix_view m_array = gsl_matrix_view_array(&a[0][0], 3, 3);
    //该函数切二维数组效果同 gsl_matrix_submatrix ，避免上述问题
    gsl_matrix_view m_array2 = gsl_matrix_view_array_with_tda(&a[0][0], 3, 3,5);

    printf("m:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%g", gsl_matrix_get(m, i, j));
        }
        printf(" \n");
    }

    printf("m sub:\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%g", gsl_matrix_get(&m_sub.matrix, i, j));
        }
        printf(" \n");
    }

    printf("m array:\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%g", gsl_matrix_get(&m_array.matrix, i, j));
        }
        printf(" \n");
    }

      for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%g", gsl_matrix_get(&m_array2.matrix, i, j));
        }
        printf(" \n");
    }
}

```



## 向量转矩阵

```C
#include <stdio.h>
#include <gsl/gsl_matrix.h>

int matrix_vec2mat_test()
{
    int i, j;

    gsl_vector *v = gsl_vector_alloc(6);
    for (i = 0; i < 6; i++)
        gsl_vector_set(v, i, 1.5 + i);

    // 以矩阵的方式保存向量  其数据和向量为相同内存  可以矩阵方式操作向量数据
    gsl_matrix_view mv = gsl_matrix_view_vector(v, 1, 6);
    // 改动矩阵的形式
    gsl_matrix_view mv2 = gsl_matrix_view_vector_with_tda(v, 2, 3, 3);

    printf("'mv:\n");
    for (i = 0; i < 1; i++)
        for (j = 0; j < 5; j++)
            printf("%g ", gsl_matrix_get(&mv.matrix, i, j));
}
 
```



## 矩阵中提取向量

```C
#include <stdio.h>
#include <gsl/gsl_matrix.h>
 
int matrix_mat2vec_test()
{
    gsl_matrix *m = gsl_matrix_alloc(5, 5);
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            gsl_matrix_set(m, i, j, 2 + i + j);

    // 取行列
    gsl_vector_view v_row = gsl_matrix_row(m, 2);
    gsl_vector_view v_col = gsl_matrix_column(m, 2); 
    printf("%g\n", v_row);
    printf("%g\n", v_col);
	
    // 取部分行列
    gsl_vector_view v_sub_row = gsl_matrix_subrow(m, 2, 1, 3);
    gsl_vector_view v_sub_col = gsl_matrix_subcolumn(m, 2, 1, 3);
    printf("%g\n", v_sub_row);
    printf("%g\n", v_sub_col);

    //取对角求迹
    gsl_vector_view v_diag = gsl_matrix_diagonal(m);
    printf("%g\n", v_diag);

    // 取对角 向下+1
    gsl_vector_view v_sub_diag = gsl_matrix_subdiagonal(m, 1);
    printf("%g\n", v_sub_diag);

    // 取对角 向上+1
    gsl_vector_view v_sup_diag = gsl_matrix_superdiagonal(m, 1);
    printf("%g\n", v_sup_diag);

    return 0;
}

```



## 矩阵运算函数

```C
#include <stdio.h>
#include <gsl/gsl_matrix.h>
 
int matrix_calc_test()
{
    gsl_matrix *m = gsl_matrix_alloc(5, 5);
    gsl_matrix *n = gsl_matrix_alloc(5, 5);
    gsl_vector *v = gsl_vector_alloc(5);

    int i, j;
    for (i = 0; i < 5; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
        for (j = 0; j < 5; j++)
        {
            gsl_matrix_set(m, i, j, 2 + i + j);
            gsl_matrix_set(m, i, j, 6 + i + j);
        }
    }

    //=======注意下面所有操作都是直接修改m的值=======

    gsl_matrix_add(m, n);          // 矩阵相加
    gsl_matrix_sub(m, n);          // 矩阵相减
    gsl_matrix_mul_elements(m, n); // 矩阵对应元素相乘
    gsl_matrix_div_elements(m, n); // 矩阵对应元素相除

    gsl_matrix_scale(m, 2.0);        // 矩阵数乘
    gsl_matrix_add_constant(m, 5.0); // 矩阵加常数

    gsl_matrix_scale_rows(m, v);    // 矩阵行数乘
    gsl_matrix_scale_columns(m, v); // 矩阵列数乘
}
```



