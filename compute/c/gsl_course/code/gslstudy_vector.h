#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_vector_complex.h>

int vector_define_test()
{
    gsl_vector *v = gsl_vector_alloc(3);  // 分配一个长度为3的向量，但是没有初始化
    gsl_vector *w = gsl_vector_calloc(3); // 分配一个长度为3的向量，并且初始化为0

    gsl_vector_complex *u = gsl_vector_complex_alloc(3); // 指定为复数类型

    // calculate
    gsl_vector_free(v);
    gsl_vector_free(w);
}

int vector_set_test()
{
    gsl_vector *v = gsl_vector_alloc(3);                 // 分配一个长度为3的向量，但是没有初始化
    gsl_vector *w = gsl_vector_calloc(3);                // 分配一个长度为3的向量，并且初始化为0
    gsl_vector_complex *u = gsl_vector_complex_alloc(3); // 指定为复数类型

    // calculate
    for (int i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
        gsl_vector_set(w, i, 0.0 + i);
    }
    // ==
    gsl_vector_set_all(v, 1.0); // 这个函数用于设置向量v的所有元素值为1
    gsl_vector_set_zero(w);     // 这个函数用于设置向量v的所有元素值为0
    gsl_vector_set_basis(v, 1); // 这个函数用于设置向量v的第1个元素的值为1，其他元素为0
    // print
    for (int i = 0; i < 3; i++)
    {
        printf("v_%d = %g\n", i, gsl_vector_get(v, i));
        printf("v_%d = %g\n", i, gsl_vector_get(w, i));
    }

    gsl_vector_free(v);
    gsl_vector_free(w);
}

int vector_file_test()
{
    gsl_vector *v = gsl_vector_alloc(3);                 // 分配一个长度为3的向量，但是没有初始化
    gsl_vector *w = gsl_vector_calloc(3);                // 分配一个长度为3的向量，并且初始化为0
    gsl_vector_complex *u = gsl_vector_complex_alloc(3); // 指定为复数类型

    gsl_vector_set_all(v, 1.1); // 这个函数用于设置向量v的所有元素值为1
    gsl_vector_set_all(w, 0.5); // 这个函数用于设置向量v的所有元素值为1

    gsl_vector_fwrite(stdout, v);        // 这个函数用于将向量v中的内容写入二进制文件流stdout中
    gsl_vector_fread(stdin, w);          // 这个函数用于从文件流stdin中读取到向量w中
    gsl_vector_fprintf(stdout, v, "%g"); // 这个函数用于将向量v中的内容写入文本文件流stdout中
    gsl_vector_fscanf(stdin, w);         // 这个函数用于从文件流stdin中读取到向量w中

    // print
    for (int i = 0; i < 3; i++)
    {
        printf("v_%d = %g\n", i, gsl_vector_get(v, i));
        printf("v_%d = %g\n", i, gsl_vector_get(w, i));
    }

    gsl_vector_free(v);
    gsl_vector_free(w);
}

int vector_subview_test()
{
    gsl_vector *v = gsl_vector_calloc(8);
    gsl_vector *w = gsl_vector_calloc(3);

    for (int i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
        gsl_vector_set(w, i, 0.0 + i);
    }

    // 这个函数表示用于获得向量v的子向量，从第1个元素开始，长度为2
    gsl_vector_view subv = gsl_vector_subvector(v, 1, 2);
    // 这个函数用于获得向量v的子向量，从第0个向量开始，长度为2，步长为2
    gsl_vector_view subv1 = gsl_vector_subvector_with_stride(v, 0, 2, 2);
    // 1从数组中获取向量，从第0个元素开始，长度为2
    gsl_vector_view subv2 = gsl_vector_view_array(v->data, 2);

    // 只是提供了原数据的指针  值被修改会影响原数据

    printf("subv:\n");
    for (int i = 0; i < subv.vector.size; i++)
        printf("&g\n", gsl_vector_get(&subv.vector, i));
    printf("subv1:\n");
    for (int i = 0; i < subv1.vector.size; i++)
        printf("&g\n", gsl_vector_get(&subv1.vector, i));
    printf("subv2:\n");
    for (int i = 0; i < subv2.vector.size; i++)
        printf("&g\n", gsl_vector_get(&subv2.vector, i));

    gsl_vector_free(v);
    gsl_vector_free(w);
}

int vector_copy_test()
{
    gsl_vector *v = gsl_vector_calloc(8);
    gsl_vector *w = gsl_vector_calloc(3);

    // 指定为复数类型
    gsl_vector_complex *u1 = gsl_vector_complex_alloc(3);
    // 指定为复数类型
    gsl_vector_complex *u2 = gsl_vector_complex_alloc(3);

    for (int i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
        gsl_vector_set(w, i, 0.0 + i);
    }

    // 这个函数用于将向量v的值复制给向量w
    gsl_vector_memcpy(w, v);
    // 这个函数用于将向量v w的值交换
    gsl_vector_swap(w, v);
    // 这个函数用于将w的复共轭复制到v
    gsl_vector_complex_conj_memcpy(u2, u1);

    gsl_vector_free(v);
    gsl_vector_free(w);
}

int vector_calc_test()
{
    gsl_vector *v = gsl_vector_calloc(8);
    gsl_vector *w = gsl_vector_calloc(3);

       for (int i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
        gsl_vector_set(w, i, 0.0 + i);
    }

    double max,min;
    gsl_vector_swap_elements(v, 1, 2);      // 这个函数用于交换向量v的第1个元素和第2个元素的值
    gsl_vector_reverse(w);                  // 这个函数用于将向量w的元素顺序反转
    gsl_vector_add(v, w);                   // 这个函数用于将向量w加到向量v的元素上
    gsl_vector_sub(v, w);                   // 这个函数用于将向量w减到向量v的元素上
    gsl_vector_mul(v, w);                   // 这个函数用于将向量w乘到向量v的元素上
    gsl_vector_div(v, w);                   // 这个函数用于将向量w除到向量v的元素上
    gsl_vector_scale(v, 2.0);               // 这个函数用于将向量v放大2.0倍
    gsl_vector_add_constant(v, 1.0);        // 这个函数用于将向量v的每个元素都加1
    double sum = gsl_vector_sum(v);         // 这个函数用于计算向量v的元素和
    gsl_vector_axpby(2.0, v, 1.0, w);       // 这个函数用于计算2.0*v+1.0*w 的结果，并且最终结果保存在w中
    max = gsl_vector_max(v);                // 这个函数用于计算向量v中元素的最大值
    min = gsl_vector_min(v);                // 这个函数用于计算向量v中元素的最小值
    gsl_vector_minmax(v, &max, &min);       // 这个函数用于计算v的最大最小值，并且存储在max和min中
    max = gsl_vector_max_index(v);          // 这个函数用于计算向量v中元素的最大值的索引
    min = gsl_vector_min_index(v);          // 这个函数用于计算向量v中元素的最小值的索引

    unsigned long maxIndex,minIndex;
    gsl_vector_minmax_index(v,&maxIndex,&minIndex); // 这个函数用于计算v的最大最小值的索引，并且存储在max和min中

    gsl_vector_free(v);
    gsl_vector_free(w);
}
