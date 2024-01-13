
$$
R = 
\left (\begin{matrix}
a & b   \\
c & d   \\ 
\end {matrix}\right )
$$



[TOC]

  

$$
\sum\limits_i^m |\vec V_i\rang \lang \vec V_i| =I
$$

 

### 相似矩阵

例：

依旧使用矩阵
$
M_{ij} = \lang e_i|M|e_j \rang
=
\left (\begin{matrix}
5 & -2     \\
-2 & 2     \\ 
\end {matrix}\right )  $   

我们之前计算过其特征值为 $m=1,6$  
特征向量

$V_1=
\frac{1}{\sqrt{5}}
\left (\begin{matrix}
1     \\
2     \\ 
\end {matrix}\right ) ,m=1$
$V_2
=
\frac{1}{\sqrt{5}}
\left (\begin{matrix}
-2     \\
1     \\ 
\end {matrix}\right ) ,m=6
$

由上述对角化得到其对角矩阵为
$D_{ij} = \lang m_i|M|m_j\rang =
\left (\begin{matrix}
1 & 0     \\
0 & 6     \\ 
\end {matrix}\right )  $

虽然我们可以使用高斯消元法做对角化 ， 但我们这里使用狄拉克符号做计算；

我们看到两个正交基  的关系其实就是一个线性变换，这里由于同原点则可看作转动

$|m_j\rang=S|e_j\rang
\rightarrow
S_{ij}=\lang e_i|S|e_j\rang 
=
\lang e_i|m_j\rang$

接下来我们需要证明如下一个相似变换：
$$
S^{-1}MS=D
$$
证：

由于S变化是转动，那么其逆矩阵即为其转置矩阵  $S^{-1}=S^\top$

$
(S^{-1}MS)_{ij}
=
(S^{\top}MS)_{ij}
= 
\sum\limits_{kw} S^{\top}_{ik}  M_{kw}  S_{wj} 
=
\sum\limits_{kw} \lang m_i|e_k\rang   \lang e_k|M|e_w\rang \lang e_w|m_j\rang 
=
\lang m_i|M|m_j\rang = m_i\delta_{ij} = D_{ij}
$

该动作叫相似转换

### 对角矩阵应用

#### 对角矩阵的计算

$D_{ij} = d_i\delta_{ij}$

$D^2_{ij}=\sum\limits_k D_{ik}D_{kj}=\sum\limits_k d_i\delta_{ik}d_j\delta_{kj} = d_i^2\delta_{ij}
\rightarrow
(D^n)_{ij}=d_i^n\delta_{ij}$

也可从相似转换看到  $M=SDS^{-1}$

$M^n=M \cdot M \cdot M... = (SDS^{-1})(SDS^{-1})(SDS^{-1})...=S(D \cdot D \cdot D ...)S^{-1}=SD^nS^{-1}$

**可见对角矩阵相乘结果还是对角矩阵**

### 交换矩阵：

$[A,B]=AB-BA=0$

$(AB)_{ij}=\sum\limits_k a_i\delta_{ik}b_k\delta_{kj}=a_ib_i\delta_{ij}$

$(BA)_{ij}=\sum\limits_k b_i\delta_{ik}a_k\delta_{kj}=b_i a_i\delta_{ij}=a_ib_i\delta_{ij}$

也可从相似转换看到,若AB为可对角化的非对角矩阵，此时矩阵是一般的样子

$A'=SAS^{-1} \rightarrow A=S^{-1}A'S$

$B'=SBS^{-1} \rightarrow B=S^{-1}B'S$

$[A',B']=A'B'-B'A' \\=
SAS^{-1} \cdot SBS^{-1} - SBS^{-1} \cdot SAS^{-1} =
SABS^{-1} - SBAS^{-1} \\=
S(AB-BA)S^{-1}=S[A,B]S^{-1}=0$

如果两个矩阵使用相同的基底都可以对角化，那么这两者为交换矩阵，即便其表达方式不一定是对角化的；

#### 例 二次曲线

<img src="temp.assets/image-20230121172730267.png" alt="image-20230121172730267" style="zoom:50%;" />

我们有公式来表达平面上的椭圆

$5x^2-4xy+2y^2=30$ 

也可以写为

$\left (\begin{matrix}
x & y    
\end {matrix}\right ) 
\left (\begin{matrix}
5 & -2     \\
-2 & 2     \\ 
\end {matrix}\right ) 
\left (\begin{matrix}
x   \\
y   \\ 
\end {matrix}\right )
=30 $

如果我们使用其对角矩阵来替换这个看起来一般的矩阵

$\left (\begin{matrix}
x' & y'    
\end {matrix}\right ) 
\left (\begin{matrix}
1 & 0     \\
0 & 6     \\ 
\end {matrix}\right ) 
\left (\begin{matrix}
x'   \\
y'   \\ 
\end {matrix}\right )
=30 
\rightarrow
x'^2+y'^2=30$

其表达就成了一个标准椭圆公式，只不过我们取的不是现有直角坐标系的基向量来表达；



-----















