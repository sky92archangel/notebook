# Introduction to PDEs（偏微分方程入门）

[TOC]

整体分为6个核心知识点：
1. What are PDEs? 什么是偏微分方程
2. Why should you care? PDEs的应用场景
3. What types of PDEs are there? PDE的分类维度
4. Homogeneity 齐次性
5. Coefficient Type 系数类型
6. Parabolic / Hyperbolic / Elliptic 二阶线性PDE的三大类型

---
## 1）What are PDEs? 偏微分方程定义
**PDE = partial differential equation**：包含多元函数及其偏导数的方程。
对比 ODE（常微分方程）：
- PDE 示例：$\displaystyle \frac{\partial f}{\partial t} = \frac{\partial^2 f}{\partial x^2}$，函数 $f(x,t)$ 含多个自变量
- ODE 示例：$\displaystyle \frac{df}{dx} = f^2$，函数 $f(x)$ 仅1个自变量

## 2）Why should you care? PDE的实际应用
- Heat Conduction 热传导方程
- Fluid Motion (Navier-Stokes) 流体运动（纳维-斯托克斯方程）
- Schrödinger’s Equation 薛定谔方程（量子力学）
- General Relativity (EFE) 广义相对论（爱因斯坦场方程）

## 3）PDE分类维度 

### a) 阶数 Order

阶数 = 方程中**最高阶偏导数**的阶数
1. $\displaystyle \frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t}$：最高二阶偏导 → **2阶 PDE**
2. $\displaystyle \frac{\partial^3 f}{\partial x^2 \partial y} = \frac{\partial f}{\partial t}$：最高三阶混合偏导 → **3阶 PDE**

### b) 自变量数量 No. of independent variables
自变量：求偏导时对应的变量（对谁求偏导，谁就是自变量）
例：$f(x,t)$ 有2个自变量 $x,t$；$f(x,y,t)$ 有3个自变量 $x,y,t$

### c) 线性 Linearity
**线性 PDE**：待求因变量（被求导的函数 $f$）仅以一次线性形式出现
- 以下两个均为线性：
  $$\frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t},\quad \frac{\partial^3 f}{\partial x^2 \partial y} = \frac{\partial f}{\partial t}$$
- $\displaystyle \frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t} \cdot \tan t$：仍为线性（仅自变量函数作为系数，不含 $f$ 的乘积/幂次）
- $\displaystyle f \cdot \frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t} \cdot \tan t$：**非线性**（出现 $f$ 与自身偏导数相乘项）

## 4）齐次性 Homogeneity
**齐次 PDE**：方程每一项只包含因变量 $f$ 或它的各阶偏导数，无不含 $f$ 的独立外源项。
- 齐次示例：
  $$\frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t},\quad \frac{\partial^3 f}{\partial x^2 \partial y} = \frac{\partial f}{\partial t}$$
- 非齐次示例：
  $$\frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t} + x^2 + \tan t$$
  右侧 $x^2、\tan t$ 是不含 $f$ 的外源项，因此非齐次。

## 5）系数类型 Coefficient Type
分为**常系数 Constant coefficients**、**变系数 Variable coefficients**
1. 常系数（所有导数前系数为常数）
    $$1\cdot \frac{\partial^2 f}{\partial x^2} = 1\cdot \frac{\partial f}{\partial t},\quad 1\cdot \frac{\partial^3 f}{\partial x^2 \partial y} = 1\cdot \frac{\partial f}{\partial t}$$
2. 变系数（导数前系数是自变量的函数）
    $$\tan x \cdot \frac{\partial^2 f}{\partial x^2} = \frac{\partial f}{\partial t}$$
    $\tan x$ 是自变量 $x$ 的函数，属于变系数 PDE

## 6）二阶线性PDE三大类型：抛物型/双曲型/椭圆型
### 标准通用二阶线性PDE形式 (A)
$$A \frac{\partial^2 f}{\partial x^2} + B \frac{\partial^2 f}{\partial x \partial y} + C \frac{\partial^2 f}{\partial y^2} + D \frac{\partial f}{\partial x} + E \frac{\partial f}{\partial y} + F f = G$$
通过判别式 $\boldsymbol{\Delta = B^2 - 4AC}$ 分类：

### ① 双曲型 Hyperbolic
条件：$\boldsymbol{B^2 - 4AC > 0}$
变量替换后标准形式：
$$\frac{\partial^2 f}{\partial \eta^2} - \frac{\partial^2 f}{\partial \varepsilon^2} + g = 0$$
$g$ 代表一阶导数/低阶项；对标二次曲线 $x^2 - y^2 = 1$（双曲线）

### ② 抛物型 Parabolic
条件：$\boldsymbol{B^2 - 4AC = 0}$
变量替换后标准形式：
$$\frac{\partial^2 f}{\partial \eta^2} + g = 0$$
对标二次曲线 $x^2 + y = 0$（抛物线）

### ③ 椭圆型 Elliptic
条件：$\boldsymbol{B^2 - 4AC < 0}$
变量替换后标准形式：
$$\frac{\partial^2 f}{\partial \eta^2} + \frac{\partial^2 f}{\partial \varepsilon^2} + g = 0$$
对标二次曲线 $x^2 + y^2 = 1$（椭圆/圆）