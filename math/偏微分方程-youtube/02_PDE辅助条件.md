# 02_偏微分方程辅助条件（初值、边值条件）

[TOC]

## 一、热方程示例验证：$\displaystyle \frac{\partial u}{\partial t} = \frac{\partial^2 u}{\partial x^2}$
### 例1：解 $u = \frac12 x^2 + t$
1. 求偏导
$$
\frac{\partial u}{\partial x} = x,\quad \frac{\partial^2 u}{\partial x^2} = 1,\quad \frac{\partial u}{\partial t} = 1
$$
2. 代入方程校验
$$
\frac{\partial u}{\partial t} = \frac{\partial^2 u}{\partial x^2} \implies 1 = 1 \quad \checkmark
$$
满足热方程，是方程的一个解。

### 例2：解 $u = e^x e^t$
$$
\frac{\partial^2 u}{\partial x^2} = e^x e^t,\quad \frac{\partial u}{\partial t} = e^x e^t
$$
代入得 $e^x e^t = e^x e^t \quad \checkmark$，同样满足方程。

### 例3：误差函数解
$\displaystyle u = \mathrm{erfc}\left(\frac{x}{2\sqrt{t}}\right)$ 也满足上述热方程。

> 说明：同一个PDE有无穷多解，必须搭配**初值/边界辅助条件**才能确定唯一解。

---

## 二、辅助条件总览：初值条件 + 边界条件
### 1）初值条件（Initial Conditions）
**定义**：在某一固定时刻，规定待求函数的取值性质。
- 标准形式示例：
$$
u(x,t_0) = f(x),\quad \left.\frac{\partial u}{\partial t}\right|_{t=t_0} = g(x)
$$
- 判定规则：
  初值条件的数量 = PDE中时间导数的最高阶数
  通用结论：若PDE最高时间导数为 $n$ 阶，则需要直到 $(n-1)$ 阶时间导数的初值条件。

> 例：热方程 $\displaystyle \frac{\partial u}{\partial t} = \frac{\partial^2 u}{\partial x^2}$，时间最高阶为1阶，仅需**1个初值条件**。

### 2）边界条件（Boundary Conditions）
**定义**：在空间定义域的边界位置，规定解的约束性质，共3大类：
#### a) Dirichlet 边界条件（第一类边值）
直接规定边界上函数 $u$ 的取值。
- 一维示例 $u(x,t)$：
$$
u(x=0,\,t) = h_1(t)
$$
- 二维示例 $u(x,y,t)$：
$$
u(x=0,\,y,\,t) = m_1(y,t)
$$

#### b) Neumann 边界条件（第二类边值）
规定边界上**空间一阶偏导数**的取值。
- 一维示例：
$$
\left.\frac{\partial u}{\partial x}\right|_{x=0} = h_2(t)
$$

#### c) Robin 边界条件（第三类边值，混合边值）
边界上约束 $u$ 与其空间导数的线性组合。
- 一维示例（$k$ 为常数）：
$$
\left.\frac{\partial u}{\partial x}\right|_{x=0} + k\left.u\right|_{x=0} = g(t)
$$

#### 边界条件数量判定规则
需要的边界条件总数 = 每个空间变量最高阶偏导数的阶数之和。
示例：
1. $\displaystyle \frac{\partial u}{\partial t} = \frac{\partial^2 u}{\partial x^2}$
   $x$ 方向最高阶2阶 → 需要 **2个边界条件**（对$x$积分两次产生2个待定常数）
2. $\displaystyle \frac{\partial u}{\partial t} = \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2}$
   $x$ 2阶 + $y$ 2阶 = 4 → 需要 **4个边界条件**
3. $\displaystyle \frac{\partial u}{\partial t} = \frac{\partial^6 u}{\partial x^6} + \frac{\partial^8 u}{\partial y^8}$
   $x$ 6阶 + $y$ 8阶 = 14 → 需要 **14个边界条件**（$x$占6个，$y$占8个）

### 3）无界区域：无穷远条件
当定义域不是有限有界区间时，需要补充无穷远处约束，示例：
$$
\int_{-\infty}^{+\infty} |u|^2 dx = 1
$$

---

## 补充注释
此外，当研究的区域不是有界的时候，还会出现其他类型的辅助条件。