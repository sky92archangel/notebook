# 动态模态分解DMD

[TOC]

## 问题描述

有150个时间点测试出的150个场数据，每个场有列向量X表达(X向量很长为m个)；有矩阵如下；
$$
X_{all}=[X_1,X_2,...,X_{150}]
$$


为了从前一步预测下一步的动态则需要构造前后两个数据场矩阵：
$$
X=[X_1,X_2,...,X_{149}]
$$

$$
Y=[X_2,X_3,...,X_{150}]
$$

设上面两个矩阵有线性关系：
$$
Y = AX
$$
此时我们求出A即可求得前后关系的线性系数了，但A的维度巨大为m*m，所以需要DMD方法进行求解其低维度相似矩阵，最后还原为A进行计算；



## DMD步骤

### 步骤1：

对X做SVD分解，做r维SVD，r远远小于m
$$
X =U\Sigma V^\dagger
\\
Y=AX=AU\Sigma V^\dagger
\to 
A U =YV\Sigma^{-1}
\\
U=XV\Sigma^{-1}
$$

### 步骤2：

把A投影到基态U矩阵，求出简化的A ， 并求简化后A矩阵的特向量矩阵和特征值对角矩阵：这里注意U需要求的逆矩阵是伪逆：
$$
\tilde A = U^\dagger A U = U^\dagger YV \Sigma^{-1}
\\
\tilde A \to eigen-vetor-matrix: W 
\\
\Lambda =W^\dagger \tilde A W,eigen-value-matrix:\Lambda
$$

### 步骤3：

将简化A的特向量矩阵还原到原来的维度，此时得到DMD模态矩阵：
$$
\Phi = UW =XV\Sigma^{-1}W
$$

### 步骤4：

其实简化的A和原始的A为相似矩阵 可经过模态矩阵构造；相似矩阵特征值相同，且 特征向量差一个变换 

工程常用的公式，这里也有伪逆：
$$
A_{k->k+p} = \Phi\Lambda^p \Phi^\dagger
$$

### 步骤5：

进行预测
$$
X_{k+p} = \Phi\Lambda^p \Phi^\dagger X_k
$$
k为起始的时间片段，p为预测的步数

 



## 解释

非线性场的线性化求解，极大减少算力开销；

### 第一步

SVD为分解出各个基态 U， 表达每个基态能量的  $\Sigma$ ，表达每个基态随着时间变化的 V，降到多少维度是由人为指定，这里降到r 
$$
X_{m\times t} =U_{m\times r}\Sigma_r V_{r\times t}^\dagger
\\
Y_{m\times t} =A_m X_{m\times t} 
=A_m U_{m\times r} \Sigma_r  V^\dagger_{r\times t} 
\\
A_m U_{m\times r} =Y_{m\times t}V_{t\times r}\Sigma^{-1}_r
\\
U_{m\times r}=X_{m\times t} V_{t\times r}\Sigma^{-1}_r
\\
m>>r
$$


### 第二步

把高维度A投影为低维度简化的A
$$
\tilde A_r = U_{r\times m}^\dagger A_m U_{m\times r} 
= U^\dagger_{r\times m} Y_{m\times t}V_{t\times r} \Sigma^{-1}_r
\\
\tilde A_r \to eigen-vetor-matrix: W_r
\\
\Lambda_r =W^\dagger_r \tilde A_r W_r \to 
eigen-value-matrix:\Lambda_r
$$

### 第三步

此时已经拿到了低维度A的特征向量向量，则求DMD模态矩阵
$$
\Phi_{m\times r} = U_{m\times r}W_r =X_{m\times t}V_{t \times r}\Sigma^{-1}_rW_r
$$

### 第四步

构造原来的高维度A矩阵

这里的简化的A和原始的A为相似矩阵，可经过模态矩阵构造；
$$
A_{m\times m} = \Phi_{m\times r}\Lambda^p_r \Phi^\dagger_{r\times m}
\\
A_{m\times m}^p = \Phi_{m\times r}\Lambda^p_r \Phi^\dagger_{r\times m}
$$

### 第五步

预测，两者相差p个时间间隔
$$
Y_{m\times t} = \Phi\Lambda^p_r \Phi^\dagger_{r\times m} X_{m\times t}
$$
































