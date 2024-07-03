#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_math.h>

int test(void)
{
    double x = 5.0;
    double y = gsl_sf_bessel_J0(x);
    printf("J0(%g) = %.18e\n", x, y);
    return 0;
}

int math_test(void)
{
    float a1, a2, a3, a4, a5, a6, a7, a8, a9;
    int b;
    a1 = gsl_log1p(1);
    a2 = gsl_expm1(1);
    a3 = gsl_hypot(3, 4);
    a4 = gsl_hypot3(1, 2, 3);
    a5 = gsl_acosh(1);
    a6 = gsl_asinh(1);
    a7 = gsl_atanh(0.5);
    a8 = gsl_ldexp(1, 2);
    a9 = gsl_frexp(4.3, &b);

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

int pow_test(void)
{

    double a1;
    a1 = gsl_pow_int(1.3, 2);
    printf("gsl_pow_int(1.3,2)= %f\n", a1);
}

int marco_test(void)
{
    int a = GSL_SIGN(-3);
    int is_odd = GSL_IS_ODD(3);
    int is_even = GSL_IS_EVEN(3);

    printf("GSL_SIGN(-3)= %d\n", a);
    printf("GSL_IS_ODD(3)= %d\n", is_odd);
    printf("GSL_IS_EVEN(3)= %d\n", is_even);
}

int max_min_test(void)
{

    double a = 21, b = 23;
    int a1 = GSL_MAX(a, b);
    printf("a1= %f\n", a1);

    double x = 1.2, y = 1.25;
    double epsilon1 = 0.1;
    double epsilon2 = 0.01;
    int result1 = gsl_fcmp(x, y, epsilon1);
    int result2 = gsl_fcmp(x, y, epsilon2);
    int result3 = gsl_fcmp(y, x, epsilon2);

    printf("x=%f,y=%f,epsilon1=%f,result1=%f",x,y,epsilon1,result1);
    printf("x=%f,y=%f,epsilon2=%f,result2=%f",x,y,epsilon2,result2);
    
    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);
}



