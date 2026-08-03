# 傅里叶变换求解偏微分方程 PDE

## 一、傅里叶变换定义
讲义采用对称形式
### 正变换
$$
\hat{f}(\omega)=\mathcal{F}\{f(x)\}=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{+\infty} f(x)e^{-i\omega x}dx
$$
### 逆变换
$$
f(x)=\mathcal{F}^{-1}\{\hat{f}(\omega)\}=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{+\infty}\hat{f}(\omega)e^{i\omega x}d\omega
$$

> ⚠️ 傅里叶变换**不是对所有函数都存在**（常数函数、$e^{x}$ 等不满足绝对可积条件），适合**全空间 $x\in(-\infty,\infty)$** 的定解问题。

---

## 二、核心思想：傅里叶变换化简微分方程
### 1. 常微分方程 ODE
$$
\frac{d^2 f}{dx^2}=g\left(x,f,\frac{df}{dx}\right)
$$
对方程做傅里叶变换：积分消去自变量 $x$，得到关于 $\hat{f}(\omega)$ 的**代数方程**；解出 $\hat{f}(\omega)$ 后做逆变换还原 $f(x)$。

### 2. 偏微分方程 PDE（热方程 $u=u(x,t)$）
$$
\frac{\partial u}{\partial t}=\alpha^2\frac{\partial^2 u}{\partial x^2}
$$
对**空间变量 $x$** 做傅里叶变换，积分消去 $x$；得到关于 $\hat{u}(\omega,t)=\mathcal{F}\{u(x,t)\}$ 的**常微分方程（仅关于 $t$）**；
解出 $\hat{u}(\omega,t)$ 后，做傅里叶逆变换得到原解 $u(x,t)$。

通用规律：
若PDE含有 $n$ 个独立变量，对其中一个变量实施傅里叶变换，得到仅含 $n-1$ 个独立变量的新方程。

### 标准三步流程

```latex

原始微分方程（含u(x)）
        ↓ STEP 1 傅里叶正变换
简化方程（关于 $\hat{u}(\omega)$）
        ↓ STEP 2 求解方程，得到 $\hat{u}(\omega)$
象函数 $\hat{u}(\omega)$
        ↓ STEP 3 傅里叶逆变换
原未知函数 u(x)
```

---

## 三、傅里叶变换核心微分性质
### 性质1：对空间变量 $x$ 的偏导（最重要）
$$
\mathcal{F}\left\{ \frac{\partial^n u}{\partial x^n} \right\}=(i\omega)^n \mathcal{F}\{u(x,t)\}
$$
**简要推导**
$$
\frac{\partial^n u}{\partial x^n}
=\frac{\partial^n}{\partial x^n}\left[
\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{\infty}\hat{u}(\omega,t)e^{i\omega x}d\omega
\right]
=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^{\infty}\hat{u}(\omega,t)\cdot (i\omega)^n e^{i\omega x}d\omega
$$
$$
\implies \mathcal{F}\left\{\frac{\partial^n u}{\partial x^n}\right\}=(i\omega)^n \hat{u}(\omega,t)
$$

### 性质2：对时间变量 $t$ 的偏导
傅里叶变换仅对 $x$ 积分，$t$ 视作参数，可以交换求导与积分顺序：
$$
\mathcal{F}\left\{ \frac{\partial^n u}{\partial t^n} \right\}
=\frac{\partial^n}{\partial t^n}\mathcal{F}\{u(x,t)\}=\frac{\partial^n \hat{u}}{\partial t^n}
$$

### 性质3：卷积定理
$$
\mathcal{F}\{f*g\}=\mathcal{F}\{f\}\cdot \mathcal{F}\{g\}
$$
逆形式：
$$
\mathcal{F}^{-1}\big\{\hat{f}(\omega)\cdot\hat{g}(\omega)\big\}=f(x)*g(x)
$$
卷积定义：
$$
(f*g)(x)=\int_{-\infty}^{+\infty}f(y)g(x-y)dy
$$

---

## 四、例题：无限长杆热传导方程（柯西问题）
### 定解问题
$$
\begin{cases}
\dfrac{\partial u}{\partial t}=\alpha^2 \dfrac{\partial^2 u}{\partial x^2},
& -\infty<x<+\infty,\ t>0 \\[4pt]
u(x,0)=\phi(x)
\end{cases}
$$

### STEP 1：对 $x$ 做傅里叶变换
记 $\hat{u}(\omega,t)=\mathcal{F}\{u(x,t)\},\quad \Psi(\omega)=\mathcal{F}\{\phi(x)\}$
利用微分性质：
$$
\mathcal{F}\left\{\frac{\partial^2 u}{\partial x^2}\right\}=(i\omega)^2 \hat{u}=-\omega^2 \hat{u}
$$
PDE变换为常微分方程：
$$
\frac{\partial \hat{u}}{\partial t}=-\alpha^2 \omega^2 \hat{u}
$$
初始条件同步变换：
$$
\hat{u}(\omega,0)=\Psi(\omega)
$$

### STEP 2：求解关于 $t$ 的常微分方程
分离变量
$$
\int \frac{d\hat{u}}{\hat{u}}=\int -\alpha^2 \omega^2 dt
\implies \ln|\hat{u}|=-\alpha^2\omega^2 t + C
$$
通解：
$$
\hat{u}(\omega,t)=A e^{-\alpha^2 \omega^2 t}
$$
代入 $t=0$ 初值条件 $\hat{u}(\omega,0)=\Psi(\omega)$，得到：
$$
\hat{u}(\omega,t)=\Psi(\omega)\cdot e^{-\alpha^2 \omega^2 t}
$$

### STEP 3：傅里叶逆变换 + 卷积定理
$$
u(x,t)=\mathcal{F}^{-1}\Big\{\Psi(\omega)\cdot e^{-\alpha^2 \omega^2 t}\Big\}
=\mathcal{F}^{-1}\Big\{\mathcal{F}\{\phi(x)\}\cdot \mathcal{F}\big\{G(x,t)\big\}\Big\}
$$
由卷积定理：
$$
u(x,t)=\phi(x)\;*\;G(x,t)
$$
**热传导格林函数（基本解）**
$$
G(x,t)=\frac{1}{2\alpha\sqrt{\pi t}} \exp\left(-\frac{x^2}{4\alpha^2 t}\right)
$$

卷积积分形式（泊松公式）：
$$
u(x,t)=\frac{1}{2\alpha\sqrt{\pi t}}
\int_{-\infty}^{+\infty} \phi(y)\exp\left(-\frac{(x-y)^2}{4\alpha^2 t}\right) dy
$$

### 格林函数物理意义
$G(x,t)$ 是初始条件为 $\phi(x)=\delta(x)$（原点瞬时点热源）时方程的解；
任意初始温度分布 $\phi(x)$ 可以分解成无穷多点热源的叠加，最终解为初始分布与格林函数的卷积。

---

## 五、傅里叶变换 VS 拉普拉斯变换求解PDE对比
| 对比项     | 傅里叶变换                     | 拉普拉斯变换                               |
| ---------- | ------------------------------ | ------------------------------------------ |
| 适用区域   | 全空间 $x\in(-\infty,\infty)$  | 半无限区域 $[0,+\infty)$                   |
| 变换自变量 | 一般取**空间变量 $x$**         | 一般取**时间变量 $t$**                     |
| 存在条件   | 要求函数绝对可积，限制较强     | 只要求指数阶增长，适用更广                 |
| 典型场景   | 无限长杆热传导、无界波动方程   | 半无限杆热传导、初值+边界条件问题          |
| 逆变换难度 | 高斯型、有理函数较易；依赖卷积 | 常出现误差函数 $\mathrm{erfc}$，依赖变换表 |

> 解题选择经验：
> 1. **无界区域 $x\in(-\infty,\infty)$** → 优先傅里叶变换
> 2. **半无界区域 $x\in[0,\infty)$，带边界条件** → 优先拉普拉斯变换

---

# 附录：拉普拉斯变换求解PDE 
## 半无限长杆热传导定解问题
$$
\begin{cases}
\dfrac{\partial u}{\partial t}=\dfrac{\partial^2 u}{\partial x^2},
& 0\le x<+\infty,\ 0\le t<+\infty \\[4pt]
u(0,t)=u_0,\quad u(x,0)=0
\end{cases}
$$
对 $t$ 拉普拉斯变换，记 $U(x,s)=\mathcal{L}\{u(x,t)\}$
$$
sU=\frac{d^2 U}{dx^2},\quad U(0,s)=\frac{u_0}{s}
$$
通解：
$$
U(x,s)=C_1 e^{\sqrt{s}\,x}+C_2 e^{-\sqrt{s}\,x}
$$
由 $x\to\infty$ 有界约束，$C_1=0$，代入边界：
$$
U(x,s)=\frac{u_0}{s}e^{-\sqrt{s}\,x}
$$
逆变换查表得到解：
$$
u(x,t)=u_0\,\mathrm{erfc}\left(\frac{x}{2\sqrt{t}}\right)
$$
互补误差函数定义：
$$ \mathrm{erfc}(y)=\frac{2}{\sqrt{\pi}}\int_{y}^{+\infty}e^{-p^2}dp $$