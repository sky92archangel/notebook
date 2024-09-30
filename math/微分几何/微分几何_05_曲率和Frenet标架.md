# 微分几何_05_曲率和Frenet标架

[TOC] 

## 曲率定义

$$
r=r(s),有二阶导\\
那么|r''(s)| 就是 曲线在点P(s)处曲率\\
记作\kappa(s)
\\
\kappa(s)=|r''(s)|
$$

曲率就是单位切向量改变量对弧长的变化率，就是描述弯曲程度了；
$$
r''(s)是曲率向量，常用于曲面论
$$
**直线的曲率处处为0**

**圆的曲率恒为非零常数**



## Frenet标架

其实就是空间曲线在某点的三个轴
$$
曲线C在每一点曲率都不为0，称
\\
\alpha(s)=r'(s)
\\
\beta(s)=\frac{r''(s)}{|r''(s)|}
\\
\gamma (s)= \frac{r'(s)\times r''(s)}{|r'(s)\times r''(s)|}
\\
三者分别为，单位切向量，主法向量，副法向量，三个模都是单位向量，且都是两两垂直；
\\
那么{P(s);\alpha(s),\beta(s),\gamma (s)}为曲线在点P(s)处的Frenet标架，三个基本向量；
$$
 其实可以看出切向量是曲线点运动朝向，副法向量是曲线该微小部分所在局部平面的法向量；

空间曲线的三个一般参数表达法
$$
\alpha(t)=\frac{r'(t)}{|r'(t)|}
\\
\beta(t)=\frac{(r'(t)\cdot r'(t))r''(t) - (r'(t)\cdot r''(t))r'(t)}{|r'(t)||r'(t)\times r''(t)|}
\\
\gamma(t)=\frac{r'(t)\times r''(t)}{|r'(t)\times r''(t)|}
\\
\kappa=\frac{r'(t)\times r''(t)}{|r'(t)|^3}
$$



$$
曲线C: r(s)在点P(s)的切线，主法线，副法线 方程，\rho为动点
\\
\rho-r = \lambda \alpha
\\
\rho-r = \lambda \beta
\\
\rho-r = \lambda \gamma
$$




和切线垂直的面 构成法平面

和主法线垂直的面 构成从切平面

和副法线垂直的面 构成密切平面
$$
(\rho-r)\cdot \alpha = 0  = (\rho-r, \beta,\gamma )
\\
(\rho-r)\cdot \beta = 0  = (\rho-r, \alpha,\gamma )
\\
(\rho-r)\cdot \gamma = 0  = (\rho-r, \alpha,\beta )
$$

密切平面就是上面说的曲线该微小部分所在局部平面的平面

密切平面的计算公式
$$
\begin{vmatrix}
x-x(t) & y-y(t) & z-z(t) \\
x'(t) & y'(t) & z'(t) \\
x''(t) & y''(t) & z''(t) \\
\end{vmatrix}
=0
$$

























