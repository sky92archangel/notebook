# 微分几何_06_挠率和Frenet公式 

[TOC]

## 前置定理

证明
$$
\gamma'(s)||\beta(s)
\\
$$
公式准备
$$
\\
\alpha(s)=r'(s)
\\
\beta(s)=\frac{r''(s)}{|r''(s)|}
\\
\gamma (s)= \frac{r'(s)\times r''(s)}{|r'(s)\times r''(s)|}
\\
\kappa(s)=|r''(s)|
$$
开始证明
$$
\beta=\frac{\gamma''}{\kappa}
\Rightarrow
\beta\kappa=\gamma''=\alpha'
\\
\gamma'=(\alpha\times\beta)'=
\alpha'\times\beta+\alpha\times\beta'=
\beta\kappa\times\beta+\alpha\times\beta'=
0+\alpha\times\beta'=
\alpha\times\beta'
\Rightarrow
\gamma'  \perp \alpha , \gamma' \perp \beta'
\\
|\gamma|=1 
\Rightarrow
\gamma' \perp \gamma
\\
\gamma'  \perp \alpha , 
\gamma' \perp \gamma
\Rightarrow
\gamma'||\beta
$$




## 引出挠率

得到平行关系后，两个向量就可以使用一个系数来表达
$$
\gamma'(s) = -\tau(s)\beta(s)
\\
\tau(s) = - \gamma'(s)\cdot\beta(s)
\\
\tau(s)为挠率
\\
|\tau(s)|=|\gamma'(s)||\beta(s)|\cos\theta,\theta=\{0,\pi\},|\beta(s)|=1
\\
所以
\\
|\tau(s)|=|\gamma'(s)|
$$
可见挠率由主法向量和副法向量决定，空间曲线的空间状态需要曲率和挠率一起决定；

曲率描述曲线的弯曲程度，即向切线方向运行单位距离时偏离切线的程度；

挠率描述曲线的扭曲程度，即沿着切线方向的滚转程度，平面曲线的挠度为0；

曲率和挠率通常相互独立；

另一种表达
$$
\tau(s) = - \gamma'(s)\cdot\beta(s)
\Rightarrow
\tau=\gamma\cdot\beta'-(\gamma\cdot\beta)'=\gamma\cdot\beta'
\\
\tau(s) =\gamma(s)\cdot\beta'(s)
$$




总结
$$
\tau(s) = - \gamma'(s)\cdot\beta(s)
\\
\tau(s) =\gamma(s)\cdot\beta'(s)
\\
|\tau(s)|=|\gamma'(s)|
$$


## 相关公式

$$
\tau(s)=\frac{(r'(s),r''(s),r'''(s))}{\kappa^2(s)}
\\
\tau(t)=\frac{(r'(t),r''(t),r'''(t))}{|r'(t)\times r''(t)|^2}
$$



### Frenet公式

三个向量的导数都可以用其原向量的线性组合表达
$$
\alpha'(s)=\kappa(s)\beta(s)
\\
\beta'(s)=-\kappa(s)\alpha(s)+\tau(s)\gamma(s)
\\
\gamma'(s)=-\tau(s)\beta(s)
$$
也可以表达为矩阵
$$
\begin{bmatrix}
\alpha'(s) \\
\beta'(s)  \\
\gamma'(s) \\
\end{bmatrix}
=
\begin{bmatrix}
0 			& \kappa(s) & 0 			\\
-\kappa(s) 	& 0  		& \tau(s) 		\\
0 			& -\tau(s) & 0 			\\
\end{bmatrix}

\begin{bmatrix}
\alpha(s) \\
\beta(s)  \\
\gamma(s) \\
\end{bmatrix}
$$

### 几何推论

$$
当曲线C在落在了平面中，成为了平面曲线，该平面的法向量为n\neq0，则
\\
r(t)\cdot n=const
\\
r(s)\cdot n=const
\\
r'(s)\cdot n=0
$$

### 应用

推论
$$
空间曲线如果在一个平面上，曲率处处不是0 \Leftrightarrow 挠率为0
\\
所有密切平面过定点的正则曲线都是平面曲线
$$














































