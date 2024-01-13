# Revit二次开发培训大纲



[TOC]

## 总述

环境配置及自身操作

C#基本语法及其外延库应用

API库

工程特殊程序架构介绍

实例操作



## 第一章  环境配置及自身操作

### 0.环境REVIT2018

（1）安装 

### 1.软件简介

（1）几何引擎+项目数据管理器 = REVIT本质

（2）文档操作单线程 向下不兼容问题 文档格式较为封闭  

（3）rvt rte rfa 各文件特点

### 2.基本操作 

（1）rvt rte rfa 关系以及使用方法

（2）切图 属性 特点 各部件的生成绘制等

### 3.几何构件

（1）几何理论

（2）rfa内部建立 几何拉伸 挖空 放样 扫略 旋转等操作 属性建立等

### 4.非代码扩展

（1）有限元仿真内容简介

（2）族属性使用技巧等非代码扩展方法



## 第二章 C#基本语法及其外延库应用

### 0.环境

VS2019 

### 1.基本概念及语法

编译器和框架   netcore  framework

namespace  class  method   代码的三种基础运行 

### 2.进阶

 多线程 调试基础 泛型编程 设计模式

### 3.第三方库及操作

 NPOI SQLITE DAPPER LITJSON



## 第三章 图形理论R-API

### 0.环境

（1）RevitLookup工具 

下载链接，使用git clone

https://github.com/jeremytammik/RevitLookup

https://github.com/jeremytammik/RevitLookup.git 

（2）Revit-SDK安装 

https://www.autodesk.com/developer-network/platform-technologies/revit

（3）AddinManager工具

Autodesk的官方插件，用来加载Revit插件，课在Revit运行时加载插件并运行，其包含在RevitSDK中；

（4）ILSpy

常用于NET的反射工具，可以用来查看类和函数；该工具常用于反编译；若是想要窥探NET库的内部代码结构，同样可以使用该工具进行查看；

 

### 1.首个Revit插件 

#### （1）工程建立

**创建项目**

打开 Visual Studio  --> 创建新项目

首先我们需要选择工程模板

此处我们需要建立库，对于REVIT开发的插件，最终的表现形式为dll文件，作为类库被REVIT主程序调用；

若用户安装的是Visual Studio 2019，则又如下界面，此处编译框架需要选择 【类库 Framework】；

![image-20210504201940840](REVIT及二次开发培训XXX.assets/image-20210504201940840.png)

注意 【类库（.NET Core）】选项，由于.NET Core 5 已由微软发布，但考虑到用户机可能未安装.NET Core环境，为了能将开发的代码在用户微机可运行，此处保守选择Framework；

**配置项目**

![image-20210504204138599](REVIT及二次开发培训XXX.assets/image-20210504204138599.png)

创建项目名称，解决方案名称会自动根据项目名称变化；

鉴于微软近年来计划将Framework编译框架并入.NET Core，并逐步停止旧版本Framework维护； 故关于Framework版本，建议选择版本Framework 4.7.2或Framework 4.8 ；

当然在工程建立后，依旧可以更换编译框架；

**工程结构**

在建立工程后可看到如下界面

![image-20210504205628936](REVIT及二次开发培训XXX.assets/image-20210504205628936.png)

在右侧 【 解决方案资源管理器 】中见到解决方案结构；

解决方案下带有同名工程，工程下带有 属性Properies、引用Reference、默认主程序cs文件Class1.cs；

Properies下有文件AssemblyInfo ，内部有关程序集的一般信息由以下控制。更改这些特性值可修改与程序集关联的信息 。

在一个解决方案下可以创建多个不同名的工程，后期复杂工程将会使用到，当然此处无需过于复杂的结构； 

**引入库**

完成基本的工程建立后我们需要进行RevitAPI的引入，在上述图中可见，工程模板中已经默认带有部分框架内存在的常用库，此时对引用右键菜单--添加引用，打开引用管理器界面

![image-20210504213026205](REVIT及二次开发培训XXX.assets/image-20210504213026205.png)

 浏览引入Revit安装的根目录找到文件RevitAPI.dll及RevitAPIUI.dll ，并勾选，确定；

![image-20210504213123708](REVIT及二次开发培训XXX.assets/image-20210504213123708.png)

此时API程序集文件已进入了当前工程的引用；

引入了RevitAPI.dll后，可以在当前工程内使用Revit中DB级别的资源接口，如文档保存，属性操作等；

引入了RevitAPIUI.dll后，可以在当前工程内使用Revit界面资源，如按钮显示，工程内实例选择等

关于以上两个程序集具体内会在API详解一节中更加深入讨论；

接下来我们可以正式开始编码了；

#### （2） 主程入口

打开默认Class1.cs或新建里一个cs文件

VS2019默认快捷键Ctrl+Shift+A，打开添加新项，此处选择类，将该文件改名为HelloRevit，该名字即为功能类名；

![image-20210504214443078](REVIT及二次开发培训XXX.assets/image-20210504214443078.png)

**简单主程**

如下是最简单的主程入口，作为插件功能运行的入口；

```c#
using Autodesk.Revit.Attributes;
using Autodesk.Revit.DB;
using Autodesk.Revit.UI; 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace  HelloRevit
{
    [Transaction(TransactionMode.Manual)]
    [Regeneration(RegenerationOption.Manual)]
    [Journaling(JournalingMode.UsingCommandData)]
    
    class HelloCommand : IExternalCommand
    {
        public Result Execute(ExternalCommandData commandData, ref string message, ElementSet elements)
        {
           	TaskDialog.Shopw("Title","Hello Revit !"); 
 			//MessageBox.Show("Hello Revit !");
            return Result.Succeeded;
        }
    }
} 
```

以上代码需要注意几点：

如下属性必须在插件功能入口添加，否则将在AddInManager加载时无法识别该主程入口

```c#
[Transaction(TransactionMode.Manual)]
[Regeneration(RegenerationOption.Manual)]
[Journaling(JournalingMode.UsingCommandData)]
```
开发人员可以使用IExternalCommand接口添加自己的功能，可以通过快捷键Alt+Enter可以对接口进行不全，补全后产生Execute方法，该方法写法固定，不建议修改；

```c#
 class HelloCommand : IExternalCommand
    {
        public Result Execute(ExternalCommandData commandData, ref string message, ElementSet elements)
        { 
        	//主程正式执行代码
        }
    }
```



当完成主程序之后，F6编译；







### 2.RIBBON按钮文件的介绍

#### （1）基本结构

```c#
using Autodesk.Revit.Attributes;
using Autodesk.Revit.UI;
using System;
//using ...

namespace SEPD.PrimaryElectrical.Draw
{
    [TransactionAttribute(TransactionMode.Manual)]
    [Regeneration(RegenerationOption.Manual)]

    public class PrimaryElectricalDrawRibbon : IExternalApplication
    { 
    	public Result OnShutdown(UIControlledApplication application)
        {  
            //在Revit关闭时  该插件需要做的事情
            return Result.Succeeded; 
        }  
    	public Result OnStartup(UIControlledApplication application)
        { 
           	//在Revit打开时 该插件需要做的事情 如开始定义加载菜单。。。 
        }
    }
```

```c#
//获得当前dll运行的绝对路径及目录
public static string assemblyPath = Assembly.GetExecutingAssembly().Location;
public static string assemblyDir = Path.GetDirectoryName(assemblyPath) + "\\";
```

接下来我们定义图像，此处我们需要在工程内创建一个

```c#
//定义图像
              Bitmap image = Resource.ICON_ALL ;
              ImageSource imageSource = Imaging.CreateBitmapSourceFromHBitmap(
                image.GetHbitmap(),
                IntPtr.Zero,
                Int32Rect.Empty,
                BitmapSizeOptions.FromEmptyOptions()); 
```

 

#### （2）单独按钮式

```c#
RibbonPanel ribbonPanel = application.CreateRibbonPanel("SEPD架空线", "功能组的名称"); 
PushButtonData pushButtonData = new PushButtonData("功能唯一标识码", "功能按钮名称", assemblyPath, "namespace.classname");
PushButton pushButton = ribbonPanel.AddItem(pushButtonData) as PushButton;
pushButton.LargeImage = imageSource; 
```

#### （3）下拉菜单式 

分裂按钮

辅助函数

```c#
public SplitButton CreateSplitButton(RibbonPanel ribbonPanel, string code ,string splitButtonName)
        {
            SplitButtonData _SpliteButtonData = new SplitButtonData(code + splitButtonName,
              splitButtonName);
            SplitButton _SplitButton = ribbonPanel.AddItem(_SpliteButtonData) as SplitButton;
            _SplitButton.IsSynchronizedWithCurrentItem = false;
            return _SplitButton; 
        } 

public PushButton CreateSplitPushButton
            (SplitButton splitButton, string assemblyPath, string code, string buttonName ,string clsPath, Bitmap image)
        { 
            PushButton _PushButton =
            splitButton.AddPushButton(new PushButtonData(code + " " + buttonName,
             buttonName,
            assemblyPath, clsPath));
            _PushButton.ToolTip = buttonName; 
            //定义图像
              Bitmap image = Resource.ICON_ALL ;
              ImageSource imageSource = Imaging.CreateBitmapSourceFromHBitmap(
                image.GetHbitmap(),
                IntPtr.Zero,
                Int32Rect.Empty,
                BitmapSizeOptions.FromEmptyOptions()); 
            //赋值
            _PushButton.LargeImage = imageSource;
        } 
```

 用法

```c#
application.CreateRibbonTab("ribbonTabName");
RibbonPanel ribbonPanel = application.CreateRibbonPanel(ribbonTabName, "RibbonPanel");
//=================================
SplitButton splitButton = CreateSplitButton(ribbonPanel, "唯一标识码", "分裂按钮名"); 
//=================================
PushButton pushButton1 = CreateSplitPushButton(splitButton, assemblyPath, "按钮1唯一标识码","功能名1", "namespace.classname1", Resource.ICON_01);
//-------------------------- 
PushButton pushButton2 = CreateSplitPushButton(splitButton, assemblyPath, "按钮2唯一标识码","功能名2", "namespace.classname2", Resource.ICON_02);
//-------------------------- 
```

 

### 3.工程文档信息结构

document内部结构



### 4.API详解

见SDK 常用类型  



#### （1）点线面



### 5.图形空间基础理论

 见图形学  基础MVP线性代数



介绍Transform变换类



boundingbox与section切图视角的举例



## 第四章 工程特殊程序架构介绍

### 0.环境

第三方库下载安装配置

第三方库可经由多种渠道获得

开发人员可以使用VS自带nuget工具直接进行线上安装，多数流行的第三方库都会提供nuget安装，如DAPPER LITJSON；

部分流行的第三方库可在官网源码形式给出，如SQLITE DAPPER等，同时官网也会提供编译好的DLL动态库文件；

如用到的库较为小众 ，则可以取github上寻找源码，下载后进行本地编译为可用的库；



### 1.API扩展详解

#### （1）扩展库写法

扩展库写法运用了C#语法中的扩展方法

首先来看扩展方法的写法于用法，如下列出两个扩展方法的写法：

**MEPCurve的基线获取**

```c#
/// <summary>
/// 获取MEPCurve（包括Pipe和Duct）的基线
/// </summary>
/// <param name="mep">线实体或占位符</param>
/// <returns></returns>
public static Line LocationLine(this MEPCurve mep)
{
    var line = (mep.Location as LocationCurve).Curve as Line;
    return line;
}
```

上述方法获取电气类管道类型MEPCurve的基线，返回Line类型； 

该扩展方法使用形式如下：

```c#
Line mepLine = mepCurve.LocationLine();
```

*再来看稍复杂的方法* 

**点是否在线段上** 

判断点是否在线段上的方法如下：

```c#
/// <summary>
/// 判断点是否在线段上
/// </summary>
/// <param name="point">需要判断的点</param>
/// <param name="line">判断的参照线段</param>
/// <returns></returns>
public static bool IsOnSegment(this XYZ point, Curve curve)
{
    if (curve.Project(point) == null) //找出点在线上的投影
    { return false; }
    
    //获得的投影点和需要判断的点point比较 是否同位置
    bool flag1 = curve.Project(point).XYZPoint.IsAlmostEqualTo(point);
    return flag1;
} 
```

上述代码使用Curve类型自带的Project方法找出点在线上的投影，若未获得投影则返回false，若获得投影点，将其和需要判断的点point比较，XYZ类型自带的IsAlmostEqualTo方法检查是否两点在近似的同位置，若是则说明point和投影点重合，那么point即为投影点，返回true；

该扩展方法使用形式如下：

```c#
bool isOnCurve = point.IsOnSegment(curve);
```

#### （2）扩展库特点

上述扩展方法都为静态方法，且在某个参数前带有this，在使用时该带有this的参数不在传参括号内，而在方法名前方作为调用；

故该this可以对该参数的类型（如XYZ）添加扩展方法，只要和扩展方法在同一个命名空间下的所有XYZ都有效，可使用该扩展方法；

.Net内部也有很多定义的扩展方法，例如我们Linq常用的Where(x=>x==true)、Select()等等；此时已经完成了使用扩展方法实现简单的函数式编程；

扩展方法需要注意：

- 扩展方法不能和调用的方法放到同一个类中；
- 扩展方法所在的类必须是静态类； 
- 第一个参数必须要，并且必须是this，这是扩展方法的标识。如果方法里面还要传入其他参数，可以在后面追加参数；
- 最好保证扩展方法和调用方法在同一个命名空间下，当然也可以在调用处引用扩展方法的命名空间；

 



### 2.可视化框架

winform  WPF  browser  

winform 和WPF的一般用法

### 3.数据存储交互

数据库的交互方式

NPOI SQLITE DAPPER LITJSON  

xml json excel txt sqlite database 文本及表交互

表操作与泛型结合运用

### 4.工程常用框架及设计技巧

外部事件使用方法

WPF的特殊用法

MVVM prime框架 观察者  

模板方法

多线程



## 第五章 实例操作

### 0.环境及工程设计哲学思想

目的  手段   交互体验   模态窗口  非模态窗口

开发的最终目的为摆脱REVIT自身缺陷束缚，将逻辑抽象出来，以至于最后彻底摆脱任何具体软件约束；

### 1.属性信息快速工具实现

paramter的灵活运用  数据文件交互

### 2.文件管理工具实现

文档库管理 sqlsever ftp

### 3.悬链线生成与距离测算算法实现

空间弧线对的最短距离及精度控制

见论文



