# 偏微分方程杜阿梅尔原理和拉普拉斯变换 Laplace Transforms and Duhamel's Principle

## 定解问题描述
有限长杆 $0<x<L$，杆侧面绝热，初始温度为0：
$$
\begin{cases}
\dfrac{\partial u}{\partial t}=\dfrac{\partial^2 u}{\partial x^2} & 0<x<L,\ t>0 \\[4pt]
u(0,t)=0,\quad u(L,t)=f(t) & \text{边界条件(B.C.)} \\[4pt]
u(x,0)=0 & \text{初始条件(I.C.)}
\end{cases}
$$
> 扩散系数 $\alpha^2=1$；边界右端为时变函数 $f(t)$。

---
## 步骤1：基准问题（简单情形 $f(t)=1$，单位阶跃边界）
记该问题解为 $u_{\text{smp}}(x,t)$。
对控制方程关于时间 $t$ 做**拉普拉斯变换**：
$$
\mathcal{L}\left\{\frac{\partial u}{\partial t}\right\}=sU_{\text{smp}}-u(x,0)
$$
代入初始条件 $u(x,0)=0$，方程转化为常微分方程：
$$
sU_{\text{smp}}=\frac{d^2 U_{\text{smp}}}{dx^2}
$$
变换域边界条件：
$$
U_{\text{smp}}(0,s)=0,\quad U_{\text{smp}}(L,s)=\frac{1}{s}
$$

### 求解常微分方程
通解形式：
$$
U_{\text{smp}}(x)=Ae^{x\sqrt{s}}+Be^{-x\sqrt{s}}
$$
代入边界 $x=0$：
$$
0=A+B \implies B=-A
$$
代入边界 $x=L$：
$$
\frac{1}{s}=A\left(e^{L\sqrt{s}}-e^{-L\sqrt{s}}\right)
$$
利用双曲正弦定义：$\displaystyle \sinh(z)=\frac{e^{z}-e^{-z}}{2}$
$$
\frac{1}{s}=2A\sinh\left(L\sqrt{s}\right)
\implies A=\frac{1}{2s\sinh\left(L\sqrt{s}\right)}
$$

带回通解：
$$
U_{\text{smp}}(x)=
\frac{1}{2s\sinh\left(L\sqrt{s}\right)}\left(e^{x\sqrt{s}}-e^{-x\sqrt{s}}\right)
=\frac{\sinh\left(x\sqrt{s}\right)}{s\sinh\left(L\sqrt{s}\right)}
$$

### 拉普拉斯逆变换得到时域解
$$
u_{\text{smp}}(x,t)=\frac{x}{L}+\frac{2}{\pi}\sum_{n=1}^{\infty}\frac{(-1)^n}{n}e^{-\left(\frac{n\pi}{L}\right)^2 t}\sin\left(\frac{n\pi x}{L}\right)
$$

---
## 步骤2：一般情形，任意 $f(t)$
设 $F(s)=\mathcal{L}\{f(t)\}$。变换域定解：
$$
\begin{cases}
sU=\dfrac{d^2 U}{dx^2}\\[4pt]
U(0,s)=0,\quad U(L,s)=F(s)
\end{cases}
$$
同理求解：
$$
U(x,s)=\frac{F(s)\sinh\left(x\sqrt{s}\right)}{\sinh\left(L\sqrt{s}\right)}
$$
变形：
$$
U(x,s)=sF(s)\cdot \frac{\sinh\left(x\sqrt{s}\right)}{s\sinh\left(L\sqrt{s}\right)}
=\mathcal{L}\{f(t)\}\cdot \mathcal{L}\left\{\frac{\partial u_{\text{smp}}}{\partial t}\right\}
$$

### 卷积定理（拉普拉斯）
$$
\mathcal{L}\{g_1*g_2\}=\mathcal{L}\{g_1\}\cdot\mathcal{L}\{g_2\}
$$
逆变换得到卷积形式：
$$
u(x,t)=f(t)*\frac{\partial u_{\text{smp}}}{\partial t}
=\int_{0}^{t}f(\tau)\,\frac{\partial u_{\text{smp}}(x,t-\tau)}{\partial t}\,d\tau
$$

---
## 步骤3：分部积分推导杜哈梅原理(Duhamel's Principle)
对卷积积分分部积分：
$$
\begin{aligned}
u(x,t)
&=\left[-f(\tau)u_{\text{smp}}(x,t-\tau)\right]_{\tau=0}^{\tau=t}
+\int_{0}^{t}u_{\text{smp}}(x,t-\tau)\,\frac{df(\tau)}{d\tau}\,d\tau \\
&=-f(t)u_{\text{smp}}(x,0)+f(0)u_{\text{smp}}(x,t)
+\int_{0}^{t}u_{\text{smp}}(x,t-\tau)\,f'(\tau)\,d\tau
\end{aligned}
$$
最终解：
$$
\boldsymbol{u(x,t)=f(0)\,u_{\text{smp}}(x,t)+\int_{0}^{t}u_{\text{smp}}(x,t-\tau)\,\frac{df(\tau)}{d\tau}\,d\tau}
$$

## 📌 Duhamel原理核心结论
> 随时间变化边界条件的PDE问题，可以由**恒定边界（$f(t)=1$）对应的基准解 $u_{\text{smp}}$**构造得到。
> 不必重新求解PDE，直接利用简单基准解叠加构造时变边界问题的解。

### 补充：拉普拉斯变换回顾
$$
\mathcal{L}\left\{f(t)\right\}=F(s)=\int_{0}^{\infty}f(t)e^{-st}dt
$$
> 适用前提：被变换自变量 $t\in[0,\infty)$。
