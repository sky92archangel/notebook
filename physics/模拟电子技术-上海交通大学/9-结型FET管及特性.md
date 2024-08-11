# 上海交通大学-模拟电子技术-笔记-9-结型FET管和特性

[TOC]

## 结型FET管

构造

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811160032111.png" alt="image-20240811160032111" style="zoom:50%;" />

对gs加压

![image-20240811160313528](C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811160313528.png)

可见Ugs增加，沟道变小，最后会彻底夹断；

那么此时如果将Ugs=const>Ugs(off)保持在工作段，增加Uds电压；

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811160831245.png" alt="image-20240811160831245" style="zoom:50%;" />

其几乎所有的工作方式和耗尽型相同

唯一区别在于Ugs必须小于0，也就是GS必须反偏；当然P沟道就相反；

**结型不容易坏，绝缘型和耗尽型的SO2太薄，容易被静电击穿，绝缘型和耗尽型易损；**

 结型的Ugs无法跨域正负，耗尽型可以做到；

## 场效应管特性

### 转移特性曲线

MOS的栅极没有电流，输入特性无法得出，所以使用转移特性，看输出特性和输入电压的比值；

转移特性曲线



N沟道增强MOS特性曲线如下

![image-20240811162212739](C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811162212739.png)
$$
i_D = I_{DO}(\frac{U_{gs}}{U_{gs(th)}}-1)^2
$$

### 输出特性曲线



![image-20240811163104672](C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811163104672.png)

### 参数

#### 直流参数 

工作电压：增强型具有Ugs(th) ， 结型和耗尽型为Ugs(off)

电流：结型和耗尽型有Idss；

直流阻值 Rgs(dc)，通常为1000兆欧，基本绝缘

#### 交流参数

跨导（低频） 
$$
g_m=\frac{\Delta i_D}{\Delta U_{GS}}|_{U_{DS}=const}
$$
极间电容，高频时会出现极间导通问题

#### 极限参数

略，选型使用
































