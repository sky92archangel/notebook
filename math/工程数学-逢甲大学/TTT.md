# 拉普拉斯变换解题笔记（完整可复制Markdown）
## 01 共轭复根 + 常微分方程初值问题
有理分式 $F(s)=\frac{N(s)}{D(s)}$，若 $(D(s)=0)$ 产生**共轭复根**，使用部分分式分解
### 例1
$$
F(s)=\frac{3s+5}{(s+1)(s^2+2s+10)}=\frac{\dfrac{2}{9}}{s+1}+\frac{As+B}{s^2+2s+10}
$$
通分：
$$
=\frac{\dfrac{2}{9}\left(s^2+2s+10\right)+(As+B)(s+1)}{(s+1)(s^2+2s+10)}
$$
比较分子多项式系数：
- $s^2$ 项：$0=\dfrac{2}{9}+A \implies \boldsymbol{A=-\dfrac{2}{9}}$
- $s^0$ 常数项：$5=\dfrac{20}{9}+B \implies \boldsymbol{B=\dfrac{25}{9}}$

代入整理：
$$
\begin{aligned}
F(s)&=\frac{2/9}{s+1}+\frac{-\dfrac{2}{9}s+\dfrac{25}{9}}{s^2+2s+10}
=\frac{2}{9}\cdot\frac{1}{s+1}+\frac{-\dfrac{2}{9}(s+1)+3}{(s+1)^2+9}\\
&=\frac{2}{9}\cdot\frac{1}{s+1}-\frac{2}{9}\cdot\frac{s+1}{(s+1)^2+3^2}+\frac{3}{(s+1)^2+3^2}
\end{aligned}
$$
拉普拉斯逆变换
$$
f(t)=\mathcal{L}^{-1}\{F(s)\}=
\frac{2}{9}e^{-t}-\frac{2}{9}e^{-t}\cos3t+e^{-t}\sin3t
$$

### 例2 二阶线性非齐次微分方程
$$
\begin{cases}
y''+4y'+13y=2e^{-2t}\\
y(0)=0,\quad y'(0)=1
\end{cases}
$$
两边做拉普拉斯变换
$$
s^2(Y(s))-sy(0)-y'(0)+4\left[s(Y(s))-y(0)\right]+13(Y(s))=\frac{2}{s+2}
$$
代入初值 $y(0)=0,y'(0)=1$
$$
(s^2+4s+13)(Y(s))-1=\frac{2}{s+2}
\implies
(s^2+4s+13)(Y(s))=\frac{s+4}{s+2}
$$
$$
(Y(s))=\frac{s+4}{(s+2)(s^2+4s+13)}
=\frac{-\dfrac{2}{9}}{s+2}+\frac{As+B}{s^2+4s+13}
$$
配成复根标准形式 $(s+2)^2+3^2$
$$
(Y(s))=\frac{-\dfrac{2}{9}}{s+2}+\frac{-\dfrac{2}{9}(s+2)+1}{(s+2)^2+3^2}
$$
逆变换：
$$
y(t)=\mathcal{L}^{-1}\{(Y(s))\}=
-\frac{2}{9}e^{-2t}-\frac{2}{9}e^{-2t}\cos3t+\frac{1}{3}e^{-2t}\sin3t
$$

---

## 02 Volterra 积分型方程（卷积方程）
标准形式
$$
y(t)=f(t)+\int_0^t a(t-\lambda)y(\lambda)d\lambda
$$
利用卷积定理 $\mathcal{L}\left\{\int_0^t a(t-\lambda)y(\lambda)d\lambda\right\}=A(s)(Y(s))$
$$
(Y(s))=F(s)+A(s)(Y(s))
\implies
\boldsymbol{(Y(s))=\frac{F(s)}{1-A(s)}}
$$

### 例1
$$
y(t)=te^t-2\int_0^t e^{(t-\lambda)}y(\lambda)d\lambda
$$
变换：
$$
(Y(s))=\frac{1}{(s-1)^2}-2\cdot\frac{1}{s-1}(Y(s))
$$
$$
\frac{s+1}{s-1}(Y(s))=\frac{1}{(s-1)^2}
\implies
(Y(s))=\frac{1}{(s-1)(s+1)}=\frac{-\dfrac{1}{2}}{s-1}+\frac{\dfrac{1}{2}}{s+1}
$$
$$
y(t)=-\frac{1}{2}e^{t}+\frac{1}{2}e^{-t}
$$

### 例2
$$
y(t)=3t^2-e^t\int_0^t y(\lambda)e^{-\lambda}d\lambda
$$
改写卷积形式：
$$
y(t)=3t^2-\int_0^t y(\lambda)e^{(t-\lambda)}d\lambda
$$
拉普拉斯变换
$$
(Y(s))=3\cdot\frac{2}{s^3}-\frac{1}{s-1}(Y(s))
$$
$$
\frac{s}{s-1}(Y(s))=\frac{6}{s^3}
\implies
(Y(s))=\frac{6(s-1)}{s^4}=\frac{6}{s^3}-\frac{6}{s^4}
$$
$$
y(t)=\mathcal{L}^{-1}\{(Y(s))\}=3t^2-t^3
$$

---

## 03 周期函数的拉普拉斯变换
设周期函数 $(f(t)=f(t+T))$，最小正周期 $T$
$$
\mathcal{L}\{f(t)\}=\frac{1}{1-e^{-sT}}\int_0^T f(t)e^{-st}dt
$$
**公式**：
$$
\boldsymbol{F(s)=\frac{1}{1-e^{-sT}}\cdot F_1(s),\quad F_1(s)=\int_0^T f(t)e^{-st}dt}
$$

### 例1
周期 $(T=2)$，一个周期内 $f(t)=1,\ t\in[0,1];\ f(t)=0,\ t\in(1,2]$
$$
\begin{aligned}
F(s)&=\frac{1}{1-e^{-2s}}\int_0^1 1\cdot e^{-st}dt
=\frac{1}{1-e^{-2s}}\cdot\left.\frac{-1}{s}e^{-st}\right|_0^1\\
&=\frac{1}{1-e^{-2s}}\cdot\frac{1-e^{-s}}{s}
=\frac{1}{s(1+e^{-s})}
\end{aligned}
$$

### 例2
周期 $(T=4)$，一个周期 $([0,2])$ 为1，$((2,4])$为0
$$
\begin{aligned}
F(s)&=\frac{1}{1-e^{-4s}}\int_0^2 e^{-st}dt
=\frac{1}{1-e^{-4s}}\cdot\frac{1-e^{-2s}}{s}\\
&=\frac{(1-e^{-2s})}{s(1-e^{-4s})}=\frac{1}{s(1+e^{-2s})}
\end{aligned}
$$

---

## 04 含延迟算子 $e^{-as}$ 逆变换；RC电路实例
时移性质：
$$
\mathcal{L}^{-1}\{e^{-as}F(s)\}=f(t-a)H(t-a)
$$
$(H(t))$ 为单位阶跃函数

### 例1
$$
F(s)=\frac{1}{s(1+e^{-s})}=\frac{1}{s}\cdot\frac{1}{1+e^{-s}}
$$
几何级数展开 $\dfrac{1}{1+x}=1-x+x^2-x^3+\cdots,\ x=-e^{-s}$
$$
F(s)=\frac{1}{s}\big(1-e^{-s}+e^{-2s}-e^{-3s}+\cdots\big)
$$
逐项逆变换
$$
f(t)=(H(t))-H(t-1)+H(t-2)-H(t-3)+\cdots
$$

### 例2 RC电路
电路参数：$R=\dfrac12\,\Omega,\ C=1\,\text{F},\ V_C(0)=1\,\text{V}$
输入脉冲序列 $V_i(t)=\sum_{n=0}^{\infty}\delta(t-n)$
电路方程
$$
RC\frac{dV_C}{dt}+V_C(t)=V_i(t)
\implies
\frac12V_C'+V_C=V_i
$$
拉普拉斯变换
$$
\frac12\left[sV_C(s)-V_C(0)\right]+V_C(s)=V_i(s)
$$
$$
(s+2)V_C(s)-2=2V_i(s),\quad V_i(s)=1+e^{-s}+e^{-2s}+\cdots
$$
$$
V_C(s)=\frac{1}{s+2}\left[3+2e^{-s}+2e^{-2s}+2e^{-3s}+\cdots\right]
$$
逆变换
$$
V_C(t)=3e^{-2t}(H(t))+\sum_{n=1}^{\infty}2e^{-2(t-n)}H(t-n)
$$

---

## 05 RLC周期脉冲电路
参数：$R=3\,\Omega,\ C=0.5\,\text{F},\ L=1\,\text{H}$，初值 $V_C(0)=0,\;V_C'(0)=2$
$$
V_i=RC\frac{dV_C}{dt}+LC\frac{d^2V_C}{dt^2}+V_C(t)
$$
代入参数
$$
V_i=\frac12V_C''+\frac32V_C'+V_C
$$
输入周期方波：
$$
V_i(t)=(H(t))-H(t-2)+H(t-4)-H(t-6)+\cdots
$$
$$
V_i(s)=\frac1s\left(1-e^{-2s}+e^{-4s}-e^{-6s}+\cdots\right)
$$
变换整理：
$$
2V_i(s)=(s^2+3s+2)V_C(s)-2
$$
$$
V_C(s)=\frac{2}{s^2+3s+2}+\frac{2}{s(s+1)(s+2)}\big(1-e^{-2s}+e^{-4s}-\cdots\big)
$$
部分分式 $\dfrac{2}{s(s+1)(s+2)}=\dfrac{1}{s}-\dfrac{2}{s+1}+\dfrac{1}{s+2}$，利用时移逐项写出分段解。

---

## 06 一阶线性微分方程组（拉普拉斯+Cramer法则）
方程组
$$
\begin{cases}
\dfrac{d(\boldsymbol{x}(t))}{dt}-2(\boldsymbol{x}(t))-3y(t)=2e^{2t}\\
-(\boldsymbol{x}(t))+\dfrac{dy(t)}{dt}-4y(t)=3e^{2t}
\end{cases},\quad
x(0)=0,\;y(0)=0
$$
拉普拉斯变换
$$
\begin{cases}
(s-2)X(s)-3(Y(s))=\dfrac{2}{s-2}\\[4pt]
-X(s)+(s-4)(Y(s))=\dfrac{3}{s-2}
\end{cases}
$$
利用**克莱姆法则**
系数行列式
$$
\Delta=
\begin{vmatrix}
s-2 & -3\\
-1 & s-4
\end{vmatrix}
=(s-2)(s-4)-3=s^2-6s+5=(s-1)(s-5)
$$
$$
X(s)=\frac{1}{\Delta}
\begin{vmatrix}
\dfrac{2}{s-2} & -3\\[4pt]
\dfrac{3}{s-2} & s-4
\end{vmatrix}
=\frac{2s+1}{(s-1)(s-5)(s-2)}
$$
$$
(Y(s))=\frac{1}{\Delta}
\begin{vmatrix}
s-2 & \dfrac{2}{s-2}\\[4pt]
-1 & \dfrac{3}{s-2}
\end{vmatrix}
=\frac{s^2-4s+6}{(s-1)(s-5)(s-2)}
$$
部分分式分解后逆变换：
$$
(\boldsymbol{x}(t))=\frac14e^t+\frac{11}{12}e^{5t}-\frac{5}{3}e^{2t}
$$
$$
y(t)=\frac14e^t+\frac{11}{12}e^{5t}-\frac23e^{2t}
$$

矩阵形式简写：
$$
\begin{bmatrix}
s-2 & -3\\
-1 & s-4
\end{bmatrix}
\begin{bmatrix}X(s)\\(Y(s))\end{bmatrix}
=\begin{bmatrix}\dfrac{2}{s-2}\\[4pt]\dfrac{3}{s-2}\end{bmatrix}
$$

---

## 07 双电感电路（微分方程组+阶跃脉冲激励）
参数：$L_1=20\,\text{H},\,L_2=30\,\text{H},\,R_1=R_2=10\,\Omega$
初始电流 $i_1(0)=i_2(0)=0$
激励 $V_{\text{in}}=5\big[H(t-2)-H(t-5)\big]$
KVL列方程
$$
\begin{cases}
V_{\text{in}}=L_1i_1'+R_1(i_1-i_2)\\
0=R_1(i_2-i_1)+L_2i_2'+R_2i_2
\end{cases}
$$
代入参数：
$$
\begin{cases}
20i_1'+10i_1-10i_2=5\big[H(t-2)-H(t-5)\big]\\
-10i_1+30i_2'+20i_2=0
\end{cases}
$$
拉普拉斯变换
$$
\begin{cases}
(6s+1)I_1(s)-2I_2(s)=\dfrac1s\left(e^{-2s}-e^{-5s}\right)\\
-I_1(s)+(3s+2)I_2(s)=0
\end{cases}
$$
求解得到 $I_1(s),I_2(s)$，利用时移性质 $e^{-as}F(s)\Rightarrow f(t-a)H(t-a)$ 写出分段电流 $i_1(t),i_2(t)$。

---

## 08 状态方程（一阶矩阵微分方程）
### 例
$$
\boldsymbol{X}'=
\begin{bmatrix}
1 & 1\\
1 & 1
\end{bmatrix}\boldsymbol{X}+
\begin{bmatrix}
e^{-2t}\\
0
\end{bmatrix},\quad
\boldsymbol{X}(0)=\begin{bmatrix}0\\0\end{bmatrix}
$$
变换：$s\boldsymbol{X}(s)-\boldsymbol{X}(0)=\boldsymbol{A}\boldsymbol{X}(s)+\boldsymbol{F}(s)$
$$
\left(s\boldsymbol{I}-\boldsymbol{A}\right)\boldsymbol{X}(s)=\begin{bmatrix}\dfrac{1}{s+2}\\[4pt]0\end{bmatrix}
$$
$$
\begin{bmatrix}
s-1 & -1\\
-1 & s-1
\end{bmatrix}\boldsymbol{X}(s)=
\begin{bmatrix}\dfrac{1}{s+2}\\[4pt]0\end{bmatrix}
$$
克莱姆法则解出 $X_1(s),X_2(s)$，部分分式分解求逆变换得到 $\boldsymbol{x}(t)$。

### 另一个状态空间模型
$$
\begin{cases}
\dot{x}_1=x_2\\
\dot{x}_2=-2x_1-3x_2+u(t)\\
y(t)=2x_1-x_2
\end{cases}
$$
拉普拉斯变换写成代数方程组：
$$
\begin{cases}
sX_1-X_2=0\\
2X_1+(s+3)X_2=\dfrac{1}{s+1}\\
Y=2X_1-X_2
\end{cases}
$$

---

## 09 高阶常微分方程、脉冲激励 $\delta(t-a)$
### 例1
$$
y''+2y'+2y=\delta(t-3),\quad y(0)=y'(0)=0
$$
变换
$$
(s^2+2s+2)(Y(s))=e^{-3s}
\implies
(Y(s))=\frac{e^{-3s}}{(s+1)^2+1}
$$
逆变换（时移）
$$
y(t)=e^{-(t-3)}\sin(t-3)\cdot H(t-3)
$$

### 例2 三阶微分方程
$$
y'''+3y''+9y'+y=30e^{-x},\quad y(0)=3,\;y'(0)=0,\;y''(0)=-47
$$
利用高阶导数拉普拉斯公式
$$
\mathcal{L}\{y'''\}=s^3(Y(s))-s^2y(0)-sy'(0)-y''(0)
$$
代入整理得到关于 $(Y(s))$ 的代数方程，部分分式求解。

### 例3 分段激励
$$
y''+y=u(t),\quad
u(t)=
\begin{cases}
0 & t<3\\
t & t\ge3
\end{cases},\quad
y(0)=0,\;y'(0)=1
$$
$$
\mathcal{L}\{u(t)\}=\int_3^{+\infty}t\,e^{-st}dt
$$
变换：
$$
(s^2+1)(Y(s))-(s\cdot0+1)=\mathcal{L}\{u(t)\}
$$

> 核心工具汇总
> 1. 导数变换：$\mathcal{L}\{y^{(n)}\}=s^n(Y(s))-\sum_{k=0}^{n-1}s^{n-1-k}y^{(k)}(0)$
> 2. 卷积定理：$\mathcal{L}\{(f*g)(t)\}=F(s)G(s)$
> 3. 时移性质：$\mathcal{L}\{f(t-a)H(t-a)\}=e^{-as}F(s)$
> 4. 周期函数公式：$\displaystyle F(s)=\frac{1}{1-e^{-sT}}\int_0^T f(t)e^{-st}dt$
> 5. 复根配型：$\mathcal{L}^{-1}\left\{\dfrac{s+a}{(s+a)^2+\omega^2}\right\}=e^{-at}\cos\omega t,\quad \mathcal{L}^{-1}\left\{\dfrac{\omega}{(s+a)^2+\omega^2}\right\}=e^{-at}\sin\omega t$

如果你需要，我可以把里面**任意一道例题单独拆成纯推导步骤，或者输出成适合直接粘贴到Latex的公式版本**。