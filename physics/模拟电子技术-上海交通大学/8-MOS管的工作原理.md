# 上海交通大学-模拟电子技术-笔记-8-MOS管的工作原理



[TOC]

## FET场效应管

一般为两种：结型场效益管、绝缘栅型场效应管（1962）

此处以绝缘栅型场效应管为例：  

绝缘栅型场效应管 -  金属氧化物场效应晶体管MOSFET - MOS管  ， 其改进型为PC机的CMOS电路；



### N沟道增强型MOS管

#### 构造

图为N沟道



<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811142749850.png" alt="image-20240811142749850" style="zoom:67%;" />

G为栅极，用于控制，相当于三极管的基极B；栅极和其他极都绝缘，故为绝缘栅；

S源极，相当于三极管的发射极E；

D漏极，相当于三极管的集电极C；

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811153600331.png" alt="image-20240811153600331" style="zoom:67%;" />

#### 工作原理

如图 

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811144411292.png" alt="image-20240811144411292" style="zoom:67%;" />

当 Ugs>0，Uds=0，时：

一开始，栅极g下方由于电场原因，会将耗尽层空穴向P衬底压迫，即为该处耗尽层电势增加，空穴减少，同时吸收电子，电子更易流入该耗尽层区域；

如果事情到此为止，那么整个电路还是没有变化的；

随着Ugs的持续增强，栅极g的电场增大，会将耗尽层电势增加，空穴减少，同时吸收电子，会在其PN结处开辟一个沟道；由于沟道内是电子，故叫做N沟道；

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811145257054.png" alt="image-20240811145257054" style="zoom:67%;" />

沟道宽度和Ugs相关，其沟道的宽度影响了D和S之间的电阻；

此时我们得到了一个用电压控制的可变电阻；
$$
U_{GS}\rightarrow R_{DS}
$$

#### 开始ds通电

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811150428284.png" alt="image-20240811150428284" style="zoom:50%;" />

Ugs(th)为开启电压，在超过此电压后时沟道出现，MOS开始工作；
所以当Ugs>Ugs(th)时沟道出现，MOS开始工作；

然后保持 Ugs=const>Ugs(th)，开始对Uds加压；
D处沟道的电压差为Ugs-Uds，当Uds不断增加，这个值Ugs-Uds就减小；
当Ugs-Uds=Ugs(th)的时候沟道就要消失了，此时状态为预夹断；
预夹断状态不是稳态，一旦夹断，ds不导通，则压降消失，此时空隙将再次打开；

再次加大Uds，预夹断的缝隙状态边长，此时电阻就上去了，那么阻值增加会阻碍Uds产生的电流，此时ds之间就有一个电流Ids的恒流区域；

**一旦进入恒流区域，其Ids只和Ugs大小相关，且成比例**

恒流时，当Ugs越大，其开辟的沟道越大，ds电阻就小，那么Id和Uds的比值就大；

<img src="C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811152209671.png" alt="image-20240811152209671" style="zoom:50%;" />

**恒流区域，其Ids只和Ugs大小相关，且成比例**

**变阻区域，其Ids和Ugs与Uds大小都相关，故状态不定**

Uds较小时，可以得到一个压控可变电阻；
Uds较大时，可得到一个压控的可变电流源；

### 耗尽型

**耗尽型MOS的沟道天生导通；**

N沟道耗尽型MOS管；

![image-20240811153003060](C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811153003060.png)

**结型MOS在绝缘层参杂正电材料，使得N沟道天然形成；** 

可见Ugs的电压方向可正可反；

Ugs+时，沟道变大，电阻小；
Ugs- 时，沟道变小，电阻大；

当增加负电压到一定程度时，沟道消失，那么就是MOS关断；
这里有个Ugs(off)，关断电压，夹断电压；

Ugs>Ugs(off)时，MOS都可以使用；



![image-20240811153539049](C:\Users\sky92\AppData\Roaming\Typora\typora-user-images\image-20240811153539049.png)

 























