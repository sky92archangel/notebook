# opencv-cpp-tutorial



[TOC]

## 100 源码编译

若不想进行源码编译，则可以使用exe直接安装；若需要完全适配当前开发环境，建议从源码开始进行编译；

假设已经安装好了  CMAKE  以及 MinGW-W64  ，并已经下载opencv 源码； 整套流程如果环境中装了MSVC，那么需要时刻规避用默认的MSVC；

如果想要使用mingw一系列的工具链，我们需要posix支持的MinGW ，推荐     x86_64-x.x.0-release-posix-seh-rt_v6-rev0   ；

建议使用CMAKE-GUI的可视化窗体做源码配置；
填入源码位置，并设定建立二进制文件存放的目录；
建议Groups Advanced 都勾选；

点击Configure

```shell
where is the source code 一栏 填入源码目录路径
where to build the binaries 一栏填写生成二进制文件存放的目录
建议Groups Advanced 都勾选
点击Configure 开始配置
会弹出需要使用的编译器，这里为了后续使用gdb 推荐使用 MinGW ，建议用native配置以防自动搜索落空，native需要直接指定 gcc g++ 的路径；
首次Configure必然会出现大量错误，接下来需要修改一些配置
Search 处查找配置关键字可修改
查找 Prefix 填入最终生成结果dll a lib 等文件的目录 即为最终安装目录，一般为build下的install 目录
若要编译contrib包，需要配置上OPENCV_EXTRA_MODULES_PATH = 源码modules路径 ，一般我们不用；
OPENCV_ENABLE_ALLOCATOR_STATS 选项取消选择可避免如下错误，这个错误是很烦人的：
---
gcc: error: long: No such file or directory
C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\windres.exe: preprocessing failed.
mingw32-make[2]: *** [modules\core\CMakeFiles\opencv_core.dir\build.make:1492: modules/core/CMakeFiles/opencv_core.dir/vs_version.rc.obj] Error 1
mingw32-make[2]: *** Waiting for unfinished jobs....
mingw32-make[1]: *** [CMakeFiles\Makefile2:1844: modules/core/CMakeFiles/opencv_core.dir/all] Error 2
---
再次点击Configure，完成后点击Generate 
完成后进入二进制文件存放目录，通常名为build，在此目录中打开命令行
输入  mingw32-make.exe -j 4  ，设定编译要用到的线程 ，4为计算机CPU线程数 ， 这一步需要耐心等待
输入  mingw32-make.exe install  ，就会开始进行安装 ， 将最终生成的文件写入之前Prefix设定的安装目录 一般为build下的install 目录

完成后 
build/install/include  有所有头文件，
build/install/x64/mingw/lib 是静态库(.a)所在目录，
build/install/x64/mingw/bin 是动态链接库(.dll)的所在目录
 
```

 注意：下面的环境配置使用的依旧是window+visual-studio 所以路径稍有出入；

## 101 环境配置搭建

### 环境准备

WIN10 + VS2019 + OPENCV4.4

官网下载 opencv-4.4.0 的 exe 文件 使用zip解压

### 开始建立

VS2019建立工程，将编译属性转为Release x64

视图 -- 其他窗口 -- 属性管理器

#### 属性管理器页面：

Release | x64 文件夹下 新建一个属性配置文件 Microsoft.Cpp.x64.user

开始配置Microsoft.Cpp.x64.user属性

通用属性 -- VC++目录 -- 包含目录 

```
...\opencv\build\include
...\opencv\build\include\opencv2
```

通用属性 -- VC++目录 -- 库目录 

```
...\opencv\build\x64\vc15\lib
```

通用属性 -- 链接器 -- 输入 -- 附加依赖项 

```
opencv_world440.lib
```

### 系统PATH配置

PATH中添加  

```
...\opencv\build\x64\vc15\bin
```

### 代码测试

新建console空项目工程

输入

```c++
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc , char** argv)
{
	Mat src = imread("此处为图片的绝对路径");
	//namedWindow("input",WINDOW_FREERATIO);
	imshow("input",src);
	waitKey(000);

	destroyAllWindows();

	return 0;
}
```

生成运行

#### 当前工程属性配置

配置属性 -- VC++目录 -- 包含目录 

```
新建当前工程目录
```

完成配置

## 102 图片读取和显示

见代码

```c++
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
 
int main(int argc , char** argv)
{
    /*
    读入图片  RGB  256X256X256
    IMREAD_GRAYSCALE为以黑白灰图方式导入图像  
    IMREAD_UNCHANGED 用于有透明通道的图片   
    IMREAD_ANYCOLOR IMREAD_ANYDEPTH 用于浮点图像 不同位图 等
    此处载入图片为  3通道 x 1字节（8位）  
    */
	Mat src = imread("此处为图片的绝对路径"，IMREAD_GRAYSCALE);
    src.depth(); //图片深度   图片深度为24位时opencv内可能枚举为1
    
    //判断图片是否空白  空白则直接返回
    if (src.empty()) 
	{
		print("could not load image ,rollback \n");
		return -1;
	} 
    // 若图像过大则自动调整窗口大小以在屏幕中全部显示
	namedWindow("input",WINDOW_FREERATIO); 
    
    //显示  imshow一般支持  256位图或浮点数据显示   其他格式可能有问题
	imshow("input",src);  
	waitKey(1000);//阻塞当前线程1000毫秒，使得上方图像保持显示 若为0则持续阻塞 
	destroyAllWindows();//关闭窗口

	return 0;
}
```

## 103 图像色彩空间转换

色彩空间转换 

新建头文件  quickdemo.h

```c++
#pragma once

#include <opencv2/opencv.hpp> 
using namespace cv; 

class QuickDemo
{
public :
	void colorSpace_Demo(Mat &image); 
};
```

实现类方法 quickdemo.cpp

```c++
//QuickDemo::colorSpace_Demo
#include <quickopencv.h> 

void QuickDemo::colorSpace_Demo(Mat& image)
{
	Mat gray, hsv;

    /*
     COLOR_BGR2HSV = 40
     COLOR_HSV2BGR = 54
     RGB  256X256X256    RGBA 256X256X256X256 
     将RBG色彩空间转为HSV色彩空间
     H 0-180  S颜色和饱和度  V亮度
    */
	cvtColor(image, hsv, COLOR_BGR2HSV);
    
    /*
    COLOR_BGR2GRAY = 6
    COLOR_GRAY2BGR = 8
    将RBG色彩空间转为灰度图空间
    */
	cvtColor(image, gray , COLOR_BGR2GRAY);
	imshow("HSV",hsv);
	imshow("GRAY",gray);
    
    //保存处理后的图像 路径  对象
	imwrite("D:/hsv.png",hsv);
	imwrite("D:/gray.png", gray);
}
```

主程

```c++
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
 
int main(int argc , char** argv)
{
    /*
    读入图片  RGB  256X256X256    RGBA 256X256X256X256 
    IMREAD_GRAYSCALE为以黑白灰图方式导入图像  
    IMREAD_UNCHANGED 用于有透明通道的图片   
    IMREAD_ANYCOLOR IMREAD_ANYDEPTH 用于浮点图像 不同位图 等
    此处载入图片为  3通道 x 1字节（8位）  
    */
	Mat src = imread("此处为图片的绝对路径"，IMREAD_GRAYSCALE);
    src.depth(); //图片深度   图片深度为24位时opencv内可能枚举为1
    
    //判断图片是否空白  空白则直接返回
    if (src.empty()) 
	{
		print("could not load image ,rollback \n");
		return -1;
	} 
    // 若图像过大则自动调整窗口大小以在屏幕中全部显示
	namedWindow("input",WINDOW_FREERATIO); 
    
    //显示  imshow一般支持  256位图或浮点数据显示   其他格式可能有问题
	imshow("input",src); 
	
	//此处引用色彩空间变化类
	QuickDemo qd; 
	qd.colorSpace_Demo(src);
	 
	
	waitKey(1000);//阻塞当前线程1000毫秒，使得上方图像保持显示 若为0则持续阻塞 
	destroyAllWindows();//关闭窗口

	return 0;
}
```

## 104 图像对象的创建和赋值

类实现quickdemo.cpp 内新增 mat_creation_demo方法

```c++
void QuickDemo::mat_creation_demo(Mat& image)
{
	Mat m1, m2;
	//克隆   	新内存
	m1 = image.clone();
	//拷贝	新内存
	image.copyTo(m2);
    
    //赋值 指针指向同内存 
    m1 = image;
 
	//创建空白图像  图像将保存为矩阵
	//8x8像素的全0矩阵   8位 U无符号 C字符 每像素1通道  全为0
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC1);
    //8x8像素的全1矩阵   8位 U无符号 C字符 每像素1通道  全为1
    Mat m4 = Mat::ones(Size(8, 8), CV_8UC1);
    //8x8像素的全1矩阵   8位 U无符号 C字符 每像素3通道  每个像素内仅首个通道为1 其余0
    Mat m5 = Mat::ones(Size(8, 8), CV_8UC3);
    
    
    
    //将每个像素第一个通道变为127
    m5 = 127;
    
    //将每个像素的所有通道变为127
    m5 = Scalar(127,127,127);
	
    imhsow("pic",m5);
    
	//算列出 得出宽度
	std::cout << m3.cols << std::endl;
	//算行数 得出高度
	std::cout << m3.rows << std::endl;
	//算每个像素所有的通道数
	std::cout << m3.channels() << std::endl;

	std::cout << m3 << std::endl;
}
```

## 105 图像像素的读写操作

一切对象皆Mat

#### 图像像素操作 一般方法

类实现quickdemo.cpp 内新增 pixel_visit_demo方法

对图像像素依次处理  获得图像反色操作  

```c++
/// <summary>
/// 对图像像素依次处理  获得图像反色操作
/// </summary>
/// <param name="image"></param>
void QuickDemo::pixel_visit_demo(Mat& image)
{
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	
	for (int row = 0; row <  h; row++)
	{ 
		for (int col = 0; col < w; col++)
		{
			//灰度图像
			if (dims == 1)
			{
                //获得当前像素点的值
				int pv = image.at<uchar>(row,col);
                //此处做反色操作  黑--白
				image.at<uchar>(row, col) = 255 - pv;
			} 
			//彩色图像
			if (dims == 3)
			{
                //获得当前像素点的三个通道 保存入vector向量数据类型内 Vec3b为保存字节  Vec3d为保存整形   其余看文档详解
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		} 
	} 
	imshow("读写演示", image); 
}
```



#### 图像像素操作 指针方法

类实现quickdemo.cpp 内新增 pixel_visit_demo_ptr方法

速度快  不依赖像素数组下标

对图像像素依次处理  获得图像反色操作 

```c++

/// <summary>
/// 对图像像素依次处理 指针处理  获得图像反色操作  
/// </summary>
/// <param name="image"></param>
void QuickDemo::pixel_visit_demo_ptr(Mat& image)
{
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	 
	for (int row = 0; row < h; row++)
	{
		//得到当前行的指针地址
		uchar* current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++)
		{
			//灰度图像
			if (dims == 1)
			{
				int pv = *current_row;
				*current_row++ = 255 - pv;
			}

			//彩色图像
			if (dims == 3)
			{
				int pv = *current_row;
			/*	*current_row++ = 255 - pv;
				*current_row++ = 255 - pv;
				*current_row++ = 255 - pv;*/

				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}

	}

	imshow("读写演示", image);

} 
```



## 106 图像像素算术操作

 类实现quickdemo.cpp 内新增 operators_demo方法  常用于调整图像亮度或某一原色的比值

算术操作建议使用内置函数

```c++


void QuickDemo::operators_demo(Mat& image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat dst2 = Mat::zeros(image.size(), image.type());

	imshow("原图", image);

#pragma region 一般方法

	dst = image + Scalar(50, 50, 50);
	imshow("调高亮度  一般加法操作", dst);
	dst = image - Scalar(50, 50, 50);
	imshow("调低亮度  一般减法操作", dst);
	dst = image / Scalar(50, 50, 50);
	imshow("调低亮度  一般除法操作", dst);

#pragma endregion

#pragma region 函数方法

	//乘法有特殊函数提供  亮度提高  至255截断  


	//新增原图同大小和类型的图像矩阵mat
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);


	//开始乘法  原图矩阵*新图像矩阵 = 需要显示的图像矩阵
	multiply(image, m, dst);
	imshow("内置方法的乘法操作", dst);

	//开始加法  原图矩阵+新图像矩阵 = 需要显示的图像矩阵
	add(image, m, dst);
	imshow("内置方法的加法操作", dst);

	//开始减法  原图矩阵-新图像矩阵 = 需要显示的图像矩阵
	subtract(image, m, dst);
	imshow("内置方法的减法操作", dst);

	//开始除法  原图矩阵/新图像矩阵 = 需要显示的图像矩阵
	divide(image, m, dst);
	imshow("内置方法的除法操作", dst);


#pragma endregion
 
	//像素乘法具体实现  
#pragma region 像素乘法具体实现
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			//彩色图像
			if (dims == 3)
			{
				Vec3b p1 = image.at<Vec3b>(row, col);
				Vec3b p2 = m.at<Vec3b>(row, col);

				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
			}
		}

	}

	for (int row = 0; row < h; row++)
	{
		//得到当前行的指针地址
		uchar* current_row_p1 = image.ptr<uchar>(row);
		uchar* current_row_p2 = m.ptr<uchar>(row);
		uchar* current_row_p3 = dst2.ptr<uchar>(row);

		for (int col = 0; col < w; col++)
		{
			//彩色图像
			if (dims == 3)
			{
				/*		*current_row_p3++ = *current_row_p1++ * *current_row_p2++;
						*current_row_p3++ = *current_row_p1++ * *current_row_p2++;
						*current_row_p3++ = *current_row_p1++ * *current_row_p2++;*/

				*current_row_p3++ = saturate_cast<uchar>(*current_row_p1++ * *current_row_p2++);
				*current_row_p3++ = saturate_cast<uchar>(*current_row_p1++ * *current_row_p2++);
				*current_row_p3++ = saturate_cast<uchar>(*current_row_p1++ * *current_row_p2++);
			}
		}
	}
	imshow("自实现指针加法", dst2);
#pragma endregion

	//--------------------

} 
```



## 107 滚动条控制图像

新增函数	tracking_bar_demo 

回调函数	on_track

```c++

Mat src, dst, m;
int lightness = 50;
//建立回调函数 此回调函数根据进度条移动同时触发 对图像进行操作
static void on_track(int, void*)
{
	m = Scalar(lightness, lightness, lightness);
	add(src,m,dst);
	imshow("亮度调整",dst);
}
void QuickDemo::tracking_bar_demo(Mat& image)
{
	src = image;
	dst = Mat::zeros(image.size(), image.type());
	m = Mat::zeros(image.size(), image.type());

    
	namedWindow("亮度调整", WINDOW_AUTOSIZE);
    //指定最大值
	int maxLightness = 100;

	//创建进度条 并指定一个回调函数  在进度条发生移动时 回调函数触发  对图像进行的操作写在回调函数内
	createTrackbar("Value Bar : ", "亮度调整", &lightness, maxLightness, on_track);
	on_track(50, 0);

}

```

## 108 滚动传参

新增回调函数	on_track_lightness

新增回调函数	on_track_contrast

```c++
/// <summary>
/// 调整亮度
/// </summary>
/// <param name="b"></param>
/// <param name="userdata"></param>
static void on_track_lightness(int b, void* userdata)
{
    // 获得void* 原图地址  则需要先把 指向void的指针void*转为 指向Mat的指针Mat*  ，随后从指针Mat*取值获得image的实际的Mat格式数据
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
    //该方法算法为  图1 * alpha + 图2 * beta + gamma = 结果图    gamma控制亮度  alpha beta控制图像素的对结果的影响占比
    //此处 对image原图显示 不引入m的影响 引入亮度gamma = b的影响
	addWeighted(image,1.0,m,0,b,dst);
	imshow("亮度对比调整",dst);
}
/// <summary>
/// 调整对比度
/// </summary>
/// <param name="b"></param>
/// <param name="userdata"></param>
static void on_track_contrast(int b, void* userdata)
{
    // 获得void* 原图地址  则需要先把 指向void的指针void*转为 指向Mat的指针Mat*  ，随后从指针Mat*取值获得image的实际的Mat格式数据
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b/100.0;
    //该方法算法为  图1 * alpha + 图2 * beta + gamma = 结果图    gamma控制亮度  alpha beta控制图像素的对结果的影响占比
    //此处只对image做动作  不引入m的影响 不引入亮度gamma = b的影响
	addWeighted(image, contrast, m, 0, 0, dst);
	imshow("亮度对比调整", dst);
}
//创建滚动条
void QuickDemo::tracking_bar_demo(Mat& image)
{ 
	namedWindow("亮度对比调整", WINDOW_AUTOSIZE);
	int maxLightness = 100;
	int lightness = 50;

	int maxContrast = 200;
	int contrast = 100;
	 
    //创建进度条 并指定一个回调函数  在进度条发生移动时 回调函数触发  对图像进行的操作写在回调函数内
    //传参 (void*)(&image)  将原图地址拿出 转为 void*指针类型 给回调函数
	createTrackbar("Light Bar : ", "亮度对比调整", &lightness, maxLightness, on_track_lightness, (void*)(&image));
	createTrackbar("Contrast Bar : ", "亮度对比调整", &contrast, maxContrast, on_track_contrast, (void*)(&image));
	on_track_lightness(50, &image);
	//on_track_contrast(60, &image); 
}


```

## 109 键盘响应操作

新增方法key_demo

```c++
//键盘动作捕捉
void QuickDemo::key_demo(Mat& image)
{ 
	Mat dst = Mat::zeros(image.size(),image.type());
	 
    //循环检测键盘动作
	while (true)
	{ 
		int c =  waitKeyEx(100);
		if (c == 27) { break; } //ESC 退出
		if (c == 49)   //key 1
		{
			std::cout << "#1" << std::endl;
			 cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50)//key 2
		{
			std::cout << "#2" << std::endl;
			 cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51)//key 3
		{
			std::cout << "#3" << std::endl;
			dst = Scalar(50,50,50);
			add(image,dst,dst);
		}
		//std::cout << c << std::endl;
		imshow("键盘响应", dst);
	} 
} 
```



## 110 自带色系滤镜

新增方法key_demo

```c++

void QuickDemo::color_style_demo(Mat& image)
{
	Mat dst;
	//颜色滤镜 新版有十九种
	int colormap[] =
	{
		COLORMAP_AUTUMN  ,
		COLORMAP_BONE  ,
		COLORMAP_JET  ,
		COLORMAP_WINTER  ,
		COLORMAP_RAINBOW ,
		COLORMAP_OCEAN ,
		COLORMAP_SUMMER  ,
		COLORMAP_SPRING  ,
		COLORMAP_COOL ,
		COLORMAP_HSV  ,
		COLORMAP_PINK ,
		COLORMAP_HOT
	};

	int index = 0;
	while (true)
	{
		int c = waitKey(70);
		if (c == 27) 
		{ break; }
		//对image应用滤镜   image原图    dst需修改的目标图
		applyColorMap(image, dst, colormap[index%12]);
		index++;
		imshow("color",dst);
	}
}


```

## 111 图像像素的逻辑操作，位操作

新增方法bitwise_demo

```c++

void QuickDemo::bitwise_demo(Mat& image)
{
    //建立两张256图片
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	//--------------------
	//图片上建立矩形  
	//rect方法前两个参数指定左上角起点 后两个指定举行宽高
	//thickness 厚度  负数为填充  正数为边缘线宽度
	// linetype参数   LINE_8默认抗锯齿   LINE_AA图形学抗锯齿   
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);

	imshow("m1", m1);
	imshow("m2", m2);
	 
    //--------------------
	///位操作
	Mat dst;
    
	// 且操作
	bitwise_and(m1, m2, dst);
    
	// 或操作
	bitwise_or(m1, m2, dst);
    
	//位操作 图像色取反操作  两种写法 
	dst= ~image;
	bitwise_not(m1, m2, dst);
    
	//图像像素异或操作
	bitwise_xor(m1, m2, dst);

	imshow("addbit", dst);

}

```

## 112 图像通道分离混合

### 图像通道分离

新增方法channels_demo

```c++
//图像通道分离 
void QuickDemo::channels_demo(Mat& image)
{
	imshow("source image", image);
	//通道分离
	std::vector<Mat> mv;
	split(image, mv);
	//此处显示只有灰色
	imshow("B", mv[0]);
	imshow("G", mv[1]);
	imshow("R", mv[2]); 
} 
```

### 通道混合

```c++
//图像通道分离混合
void QuickDemo::channels_demo(Mat& image)
{  
	//通道显示  将其他两个通道关闭为0  merge混合后 只显示2号通道的颜色
	Mat dst;
	mv[0] = 0;
	mv[1] = 0;
	merge(mv, dst);
	imshow("MR", dst);
 
	//通道混合 给出通道对换规则 0->2 1->1 2->0   
	int from_to[] = {0,2,1,1,2,0};
	//可用于多图像
	mixChannels(&image,1, &dst,1, from_to,3);
	imshow("MIX", dst);
} 
```



## 113 图像色彩空间转换2 绿幕效果

 新增方法inrange_demo

```c++

void QuickDemo::inrange_demo(Mat& image)
{
	Mat hsv  ;
	cvtColor(image,hsv,COLOR_BGR2HSV);

	Mat mask;
	//HSV 色彩空间提取   scalar内为HSV的通道取值提取范围  需查看HSV表 
	//此处提取绿色部分为分离为新图内的像素1   其余颜色在新图内为像素0  相当于对颜色做了范围遮罩
	inRange(hsv,Scalar(35,43,46),Scalar(77,255,255),mask);
	 
	//创建纯红色图
	Mat redBack = Mat::zeros(image.size(), image.type()); 
	redBack = Scalar(40, 40, 200);

	//取反 将遮罩中需要保留的部分分离为白色 即像素不为0
	//由于之前遮罩像素为1的地方是背景，则取反 将背景像素转化为 0  非背景转为1
	bitwise_not(mask,mask);
	//此处将原图拷贝到纯红图上 并添加遮罩影响， 遮罩上背景范围像素为0  则拷贝时不进行原图的背景拷贝  做到主体和背景分离效果
	image.copyTo(redBack,mask);
	 //故做到了绿幕效果
	imshow("mask", redBack);
}
```

## 114 图像像素统计

效果新增方法pixel_statistic_demo  常用于图像分析

```c++
void QuickDemo::pixel_statistic_demo(Mat& image)
{
	double maxv, minv;
	Point minLoc, maxLoc; 

    //将图像的每个通道都分离出来   由于minmaxloc函数只支持单通道图
	std::vector<Mat> mv;
	split(image, mv);
    
    //计算图片像素值的最大最小值 以及像素所在位置
	for (int i = 0; i < mv.size(); i++)
	{ 
        minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		std::cout<< "chanNo:"<< i << "min value" << minv << "max value" << maxv << std::endl;
	}
	 
    //计算图片像素的标准差以及平均值   标准差越小越接近纯色图 
	Mat mean, stddev;
	meanStdDev(image,mean,stddev);
	std::cout << "means1:" << mean.at<double>(0, 0) << endl;
	std::cout << "means2:" << mean.at<double>(1, 0) << endl;
	std::cout << "means3:" << mean.at<double>(2, 0) << endl; 
	std::cout << "stddev1:" << stddev.at<double>(0, 0) << endl;
	std::cout << "stddev2:" << stddev.at<double>(1, 0) << endl;
	std::cout << "stddev3:" << stddev.at<double>(2, 0) << endl;
  
}
```

## 115 几何图像绘制

### 绘制多边形  

新增方法drawing_geometry_demo

```c++

void QuickDemo::drawing_geometry_demo(Mat& image)
{  
    
    //矩形定义  指定开始点   指定宽高
	Rect rect;
	rect.x = 100;
	rect.y = 100; 
	rect.width = 1000;//指定宽
	rect.height = 1000; //指定高
	rectangle(image, rect, Scalar(0, 0, 255), 2, LINE_8, 0);
	//园绘制  指定中心和半径
	circle(image,Point(350,400),50, Scalar(255,0 , 255), -1, LINE_8,0);// 矩形绘制
	//线绘制  指定起终点
	line(image,Point(100,100), Point(350,400),Scalar(200,255,0),2,LINE_AA,0);
	//椭圆定义	 指定中心 长短径 焦点连线在坐标内的角度
	RotatedRect rrt;
	rrt.center = Point(200,200);//指定中心
	rrt.size= Size(100,140);// 长短径
	rrt.angle = 45;//焦点连线在坐标内的角度
	ellipse(image, rrt, Scalar(200, 255, 0), 2, LINE_AA); //绘制椭圆
	 
	imshow("draw",image); 
} 
```

###  绘制多边形并和图像混合叠加

```c++

void QuickDemo::drawing_geometry_demo(Mat& image)
{ 
    //创建纯黑色图
	Mat bg = Mat::zeros(image.size(), image.type());
	
	//矩形定义
	Rect rect;
	rect.x = 100;
	rect.y = 100; 
	rect.width = 1000;
	rect.height = 1000;	
	rectangle(bg, rect, Scalar(0, 0, 255), 2, LINE_8, 0); //在纯黑图上矩形绘制
	//园绘制
	circle(bg,Point(350,400),50, Scalar(255,0 , 255), -1, LINE_8,0);

    //将绘制的多边形和原图进行百分比混合
    Mat dst;
	addWeighted(image,0.7, bg,0.3,0,dst);
	imshow("draw", image);
}

```



## 116 随机数和随机颜色

新增方法random_demo

```c++

void QuickDemo::random_demo()
{
    //创建空画布
	Mat canvas = Mat::zeros(Size(512,512), CV_8UC3); 
	int height = canvas.rows;
	int width = canvas.cols;

    //创建随机变量
	RNG rng(12345);

	while (true)
	{ 
		int c = waitKeyEx(10);
		if (c == 27) { break; }
        
        //线的属性用随机数赋值   位置 颜色 粗细 等 全都随机
		int x1 = rng.uniform(0, width);
		int y1 = rng.uniform(0, height);
		int x2 = rng.uniform(0, width);
		int y2 = rng.uniform(0, height);
		int pr = rng.uniform(0, 255);
		int pg = rng.uniform(0, 255);
		int pb = rng.uniform(0, 255);
		int lineThickness = rng.uniform(1,8); 
		canvas = Scalar(0,0,0);//每次绘制将画布归为黑色  去除先前绘制的所有内容   若不做重置  则新图形会叠加在旧图形上绘制
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(pb, pg,  pr), lineThickness, LINE_AA, 0);
		imshow("random draw",canvas); 
	}
} 
```



## 117 随机多边形填充

### 两个方法fillPoly和polylines实现多边形填充和而边缘绘制

```c++

void QuickDemo::polyline_drawing_demo()
{
    //创建画布
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
    //创建多边形的点
	Point p1(100,100);
	Point p2(350,150);
	Point p3(500,200);
	Point p4(380,450);
	Point p5(80,200);

	//创建多边形的点
	std::vector<Point> pts;
    //将每个点压入vector中
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
 
    //------------------------------
    //下面两个方法需注意顺序
    //先填充
	fillPoly(canvas, pts, Scalar(100, 0, 255), LINE_AA,0);
    //后画边缘  该方法无法使用 thickness=-1 进行填充
	polylines(canvas,pts,true,Scalar(0,255,0),5,LINE_AA,0);
	  
	imshow("polycanvas",canvas); 
}
```

###  一个方法drawContours实现多边形填充和而边缘绘制

```c++
void QuickDemo::polyline_drawing_demo()
{
    //创建画布
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
    //创建多边形的点
	Point p1(100,100);
	Point p2(350,150);
	Point p3(500,200);
	Point p4(380,450);
	Point p5(80,200);

	//创建多边形的点
	std::vector<Point> pts;
    //将每个点压入vector中
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
    
    //------------------------------
	//创建保存多个多边形的容器
	std::vector<std::vector<Point>> contours;
	//将一组多边形压入容器
	contours.push_back(pts);
    //绘制多边形   一次可绘制多个  -1为一次性绘制所有多边形  thickness=-1 thickness=2控制填充
	drawContours(canvas,contours,-1,Scalar(0,255,200),2);
    
	imshow("polycanvas",canvas);

}
```

## 118 鼠标操作和响应

新增mouse_event_demo 

```c++

Point sp(-1,-1);
Point ep(-1,-1);
Mat tempimage;
string mousedraw = "鼠标绘制";
/// <summary>
/// 鼠标操作具体函数  该函数参数是确定的
/// </summary>
/// <param name="event">鼠标事件  为枚举值 具体查看API</param>
/// <param name="x">系统捕获的鼠标实时x位置</param>
/// <param name="y">系统捕获的鼠标实时y位置</param>
/// <param name="flags"></param>
/// <param name="userdata">传入的图像等信息</param>
static void on_draw(int event , int x ,int y ,int flags , void *userdata)
{
	Mat image = *((Mat*)userdata);
    int imageWidth = image.cols;
	int imageHeight = image.rows;
	//鼠标左键按下时动作   将按下xy位置传给起始点
	if (event == EVENT_LBUTTONDOWN)
	{
		sp.x = x;
		sp.y = y;
		std::cout << "st p" << sp << std::endl;
	}
	else if (event == EVENT_LBUTTONUP)//鼠标左键放开时动作   将放开时的xy位置传给终点 并进行后续操作
	{
		 ep.x = x;
		 ep.y = y;
        //用于保证结束点不会在图面外导致错误发生
        if (x > imageWidth)
		{ ep.x = imageWidth - 1; }
		if (y > imageHeight)
		{ ep.y = imageHeight - 1; }
		 int dx = ep.x - sp.x;
		 int dy = ep.y - sp.y; 
		//若鼠标点击是从左上画到右下 则绘制矩形
		 if (dx >= 0 && dy >= 0)
		 {   
			 //定义矩形框 
			 Rect box(sp.x, sp.y, dx, dy);
			 //将框出的矩形内的image图像的一部分取出来  取之前使用原图备份保证取得源数据的纯净
			 tempimage.copyTo(image);
			 imshow("ROI区域", image(box));   
			  
			 //开始绘制矩形
			 rectangle(image, box, Scalar(0, 255, 200), 2, 8, 0);
			 imshow(mousedraw, image);	//刷新当前图像 
			
			 //矩形绘制完成后 需要将起点归位 
			 sp.x = -1;
			 sp.y = -1;
		 }  
		 std::cout <<"dx ="<< dx<<"\tdy=" << dy << std::endl; 
	
	} 
	else if (event == EVENT_MOUSEMOVE) //此处用于点击了起点后 未点击重点 鼠标处于移动时 可以 实时看到矩形框
	{
		//当在图面上点了起点
		if (sp.x >0 || sp.y > 0)
		{
			//当前移动到的鼠标位置传给终点
			ep.x = x;
			ep.y = y;
             //用于保证结束点不会在图面外导致错误发生
            if (x > imageWidth)
            { ep.x = imageWidth - 1; }
            if (y > imageHeight)
            { ep.y = imageHeight - 1; }
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			//若鼠标点击是从左上画到右下 则绘制矩形
			if (dx >= 0 && dy >= 0)
			{ 
				//定义绘制矩形
				Rect box(sp.x, sp.y, dx, dy);
				//将原图tempimage拷贝到当前显示的图面 将移动检测时绘制的矩形刷掉 
				//则能够保证每次检测鼠标移动时绘制矩形前，图面干净
				tempimage.copyTo(image); 
				//image上绘制矩形
				rectangle(image, box, Scalar(0, 255, 200), 2, 8, 0);
				//刷新图面image
				imshow(mousedraw, image);
			} 
		}
		
	}
 
}
/// <summary>
/// 鼠标事件方法入口
/// </summary>
/// <param name="image"></param>
void QuickDemo::mouse_event_demo(Mat& image)
{ 
	//将原图拷贝一份独立内存，作为原图备份
	tempimage = image.clone();
	namedWindow(mousedraw,WINDOW_AUTOSIZE);
	//鼠标的响应函数
	setMouseCallback(mousedraw,on_draw,(void*)(&image));
	//初始化图面显示
	imshow(mousedraw, image);
}


```

## 119 图像像素类型转换和归一化



```c++
/// <summary>
/// 数据类型转换和归一化
/// </summary>
/// <param name="image"></param>
void QuickDemo::norm_demo(Mat& image)
{ 
	Mat dst; //默认CV_8UC3
	imshow("原图", image);
	std::cout << image.type() << std::endl;
	image.convertTo(image, CV_32F);	//转为32浮点型
	//image.convertTo(image, CV_32S);   //转为32整型 注意整型数据无法归一化 否则将成为全零黑图
	//格式转换后需要进行归一化才能正常显示
	normalize(image, dst, 1.0, 0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;
	imshow("图像数据归一化", dst);
}
```

## 120 图像缩放和插值



```c++
/// <summary>
/// 图像缩放和插值   三种插值  线性插值  双立方插值  lanczos插值
/// </summary>
/// <param name="image"></param>
void QuickDemo::resize_demo(Mat& image)
{
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;

	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_CUBIC);
	imshow("zoomin", zoomin);

	resize(image, zoomout, Size(w / 0.25, h / 0.25), 0, 0, INTER_CUBIC);
	imshow("zoomout", zoomout); 
}
```

## 121 图像翻转

 

```c++

/// <summary>
/// 图像反转
/// </summary>
/// <param name="image"></param>
void QuickDemo::flip_demo(Mat& image)
{
	Mat dst;
	flip(image, dst, 0);//		0上下翻转  
	flip(image, dst, 1);//		1 左右翻转    
	flip(image, dst, -1);//		-1对角线翻 转180

	imshow("flip", dst);
}

```



## 122 图像旋转

```c++

/// <summary>
/// 图像旋转
/// </summary>
/// <param name="image"></param>
void  QuickDemo::rotate_demo(Mat& image)
{
	Mat dst, M;
	int h = image.rows;
	int w = image.cols;
	//若需要先将图面缩小则重获得缩小图的长宽
	resize(image, dst, Size(w / 2, h / 2), 0, 0, INTER_CUBIC);
	h = dst.rows;
	w = dst.cols;

	//api内置旋转矩阵生成
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));
	int nw = cos * w + sin * h;
	int nh = sin * w + cos * h;

	//将旋转之后的中心和原图中心之间的偏移量预先算出加到矩阵的位移一栏里
	M.at<double>(0, 2) += (nw / 2 - w / 2);
	M.at<double>(1, 2) += (nh / 2 - h / 2);

	warpAffine(dst, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 200, 0));
	 
	imshow("rotate", dst);
}

```

## 123 视频捕捉



```c++
/// <summary>
/// 视频捕捉
/// </summary>
/// <param name="image"></param>
void QuickDemo::video_demo(Mat& image)
{
	VideoCapture capture(0);
	Mat frame;
	while (true)
	{
		capture.read(frame);
		//若无视频讯号则退出
		if (frame.empty()) { break; }
		imshow("frame", frame);

		//TODO:dosomthing
		int c = waitKey(10);
		if (c == 27) { break; }
		
	}
}
```

## 124 视频保存

SD 标清

HD 高清

UHD 超高清

```c++

/// <summary>
/// opencv 理论视频稳定处理为2G以下  若文件超过容量 另外起文件处理   
/// </summary>
/// <param name="image"></param>
void QuickDemo::videosave_demo()
{
	VideoCapture capture("D:\test1.mp4");
    //注意：set工具需要硬件支持，get使用很稳妥
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);	//高
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);	//宽
	int frame_count = capture.get(CAP_PROP_FRAME_COUNT);	//总的帧数
	double fps = capture.get(CAP_PROP_FPS);					//每秒帧数
	int fourcc = capture.get(CAP_PROP_FOURCC);				//CAP_PROP_FOURCC 原始视频的编码格式
	std::cout << "frame_height" << frame_height << std::endl;
	std::cout << "frame_width" << frame_width << std::endl;
	std::cout << "frame_count" << frame_count << std::endl;
	std::cout << "fps" << fps << std::endl;

	//保存视频
	VideoWriter vwrite("D:\test2.mp4", fourcc, fps, Size(frame_width, frame_height),true);
 
}
```

## 125 图像直方图



```c++

/// <summary>
/// 线图
/// </summary>
void QuickDemo::showHistogram_demo(Mat& image)
{
	//图像三通道分离
	vector<Mat> bgr_plane;
	split(image, bgr_plane);
	//定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };

	Mat b_hist;
	Mat g_hist;
	Mat r_hist;

	//计算blue green red 通道的直方图   支持多张图   不用mask  bins灰度级别  ranges控制值的范围
	calcHist(&bgr_plane[0],1,0,Mat(),b_hist,1,bins,ranges);
	calcHist(&bgr_plane[1],1,0,Mat(),g_hist,1,bins,ranges);
	calcHist(&bgr_plane[2],1,0,Mat(),r_hist,1,bins,ranges);
	//显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	//创建画布
	Mat histInmage = Mat::zeros(hist_h, hist_w, CV_8UC3); 
	//归一化直方图数据 让值不超出画布
	normalize(b_hist, b_hist, 0, histInmage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histInmage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histInmage.rows, NORM_MINMAX, -1, Mat());
	//绘制直方图
	for(int i  = 1; i < bins[0];i ++)
	{
		//每个像素值获得一条线
		line(histInmage,
			Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0); 
		line(histInmage,
			Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(0, 255 , 0), 2, 8, 0);  
		line(histInmage,
			Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar( 0, 0, 255), 2, 8, 0); 
	} 
	namedWindow("histogram_demo", WINDOW_AUTOSIZE);
	imshow("histogram_demo",histInmage);
	imshow("sourcePic",image);
}


```

## 126 二维直方图



```c++

/// <summary>
/// 二维直方图
/// </summary>
/// <param name="image"></param>
void QuickDemo::histogram_2d_demo(Mat& image)
{
	Mat hsv, hs_hist;
	//转到hsv
	cvtColor(image, hsv, COLOR_BGR2HSV);
    //bins为直方图内的条 h为0-180 hbins取30则步长为6 则6个内的像素值之和作为一个直方数据
	int hbins = 30;
	int sbins = 32;
	int hist_bins[] = { hbins,sbins };
	float h_range[] = { 0,180 };
	float s_range[] = { 0,256 };
	const float* hs_ranges[] = { h_range,s_range };
	int hs_channels[] = { 0,1 };
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);

	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);

	for (int h = 0; h < hbins; h++)
	{
		for (int s = 0; s < sbins; s++)
		{
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image,
				Point(h * scale, s * scale),
				Point((h + 1) * scale - 1, (s + 1) * scale - 1),
				Scalar::all(intensity),
				-1);
		}
	}
    //灰度图转到彩色图 增强人眼分辨
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);
	imshow("HS", hist2d_image);

}

```

## 127 直方图均衡化

用于提高图像识别度  医疗卫星等都常用   其实就是增强图像的色块感和颗粒度

```c++
/// <summary>
/// 灰度图像直方图均衡化
/// </summary>
/// <param name="image"></param>
void QuickDemo::histogram_eq_demo(Mat& image)
{
	//原图
	imshow("source", image); 
	//变为单通道灰度图
	Mat gray; 
	cvtColor(image, gray, COLOR_BGR2GRAY); 
	imshow("gray", gray);
	//均衡开始
	Mat dst;
	equalizeHist(gray, dst);
	imshow("eq",dst); 
} 
```

彩色图像的直方图均衡可以先转到HSV 对某通道均衡化 然后转回RGB

```c++
/// <summary>
/// 彩色图像的直方图均衡HSV
/// </summary>
/// <param name="image"></param>
void QuickDemo::histogram_eqc_demo(Mat& image)
{
	imshow("source", image);
	//原图
	Mat hsv;
    //转到HSV空间
	cvtColor(image, hsv, COLOR_BGR2HSV);
    //HSV三通道拆分
	vector<Mat> hsv_channels;
	split(hsv, hsv_channels);
	Mat V = hsv_channels.at(2);
	Mat S = hsv_channels.at(1);
	Mat H = hsv_channels.at(0);
	//对通道做直方图均衡化  效果各不相同
	//equalizeHist(H, hsv_channels.at(0));
	//equalizeHist(S, hsv_channels.at(1));
	equalizeHist(V, hsv_channels.at(2)); 
    //合并HSV三个通道
	merge(hsv_channels,hsv);
	//转回RGB图像空间
	Mat dst;
	cvtColor(hsv, dst, COLOR_HSV2BGR); 
	imshow("eq", dst);
}
```

彩色图像的直方图均衡可以直接对RGB通道均衡化 

```c++
/// <summary>
/// 彩色图像的直方图均衡RGB
/// </summary>
/// <param name="image"></param>
void QuickDemo::histogram_eqr_demo(Mat& image)
{
	imshow("source", image);
	//三通道拆分
	vector<Mat> rgb_channels;
	split(image, rgb_channels);
	Mat R = rgb_channels.at(2);
	Mat G = rgb_channels.at(1);
	Mat B = rgb_channels.at(0);
 	//对通道做直方图均衡化  效果各不相同
	equalizeHist(B, rgb_channels.at(0));
	equalizeHist(G, rgb_channels.at(1));
	equalizeHist(R, rgb_channels.at(2));
	 
	Mat dst; 
	merge(rgb_channels, dst);
	imshow("eq", dst);
}
```



## 128 图像卷积

简单图像线性卷积

定义卷积核  （可能为九宫格全1矩阵，常常为奇数）（该举例为模糊卷积）

将卷积核放到图像像素上进行遍历 ，九宫格所覆盖位置的所有像素值进行加权平均，结果替换九宫格中心位置像素值

如此往复，完成卷积

完成后图像边缘未被进行操作的一圈像素，可以舍弃也可以填充，视具体情况；

![image-20210320180943905](OpenCV_Tutorial.assets/image-20210320180943905.png)

 

```c++
/// <summary>
/// 模糊卷积
/// </summary>
/// <param name="image"></param>
void QuickDemo::blur_demo(Mat& image)
{
	Mat dst; 
    //支持XY两个方向上的卷积
	blur(image, dst, Size(5, 5),Point(-1,-1));
	imshow("source", image);
	imshow("blur",dst);
}
```



## 129 高斯卷积

简单图像高斯模糊卷积

定义卷积核  （可能为九宫格矩阵，矩阵越靠近中心数字越大 ） 此卷积核在三维图像为一个突起状态  该卷积核由高斯函数而来  故称为高斯模糊

将卷积核放到图像像素上进行遍历 ，九宫格所覆盖位置的所有像素值进行加权平均，结果替换九宫格中心位置像素值

如此往复，完成卷积

完成后图像边缘未被进行操作的一圈像素，可以舍弃也可以填充，视具体情况； 

```c++
/// <summary>
/// 高斯卷积  高斯魔模糊  一种卷积核非均匀且中间权重大于边缘权重的模糊卷积算法
/// </summary>
/// <param name="image"></param>
void QuickDemo::gaussian_blur_demo(Mat& image)
{
	Mat dst;
	GaussianBlur(image, dst, Size(9,9),31.0,1.0);
	imshow("source", image);
	imshow("gblur", dst);
}
```



## 130 高斯双边模糊



![image-20210321163521763](OpenCV_Tutorial.assets/image-20210321163521763.png)

考虑灰度的高斯模糊同时考虑RGB的色差模糊效果，两者叠加； 降噪 柔化边缘 有雾化效果；

```c++

/// <summary>
/// 双边高斯模糊 降噪 柔化边缘 有雾化效果
/// </summary>
/// <param name="image"></param>
void QuickDemo::bilateral_blur_demo(Mat& image)
{
	Mat dst; 
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("source", image);
	imshow("b-blur", dst); 
}
```



## 131 实操  人脸识别



```c++

/// <summary>
/// 
/// </summary>
/// <param name="image"></param>
void QuickDemo::face_detection_demo( )
{
	string root_dir = "Z:/_PROJECT_/OPENCV/face_detector/";
	dnn::Net net 
		= dnn::readNetFromTensorflow(
			root_dir + "opencv_face_detector_uint8.pb",
			root_dir + "opencv_face_detector.pbtxt");

	VideoCapture capture("Z:/_PROJECT_/OPENCV/Megamind.avi");
	Mat frame;
	while (true)
	{
		capture.read(frame);
		//若无视频讯号则退出
		if (frame.empty()) { break; }
		//DNN张量构建   1.0图像保持0-255色彩空间  0.0384为单一化   scalar为当前DNN模型均值文件中来    是否交换 和 剪切  false 
		Mat blob = dnn::blobFromImage(frame,1.0,Size(300,300),Scalar(104,177,123),false, false);
		//  blob  N个数  C输入通道数   H高度   W宽度
		net.setInput(blob); //NCHW
		//开始根据模型推理
		Mat probs = net.forward(); //   

		//TODO:dosomthing
		//拿到解析结果
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
		//解析
		for (int i = 0; i < detectionMat.rows; i++)
		{
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > 0.5)
			{
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
				Rect box(x1,y1,x2-x1,y2-y1);
				rectangle(frame, box, Scalar(0, 0, 255), 2, 8, 0); 
			} 
		}
		imshow("face-detec",frame);
		
		int c = waitKey(10);
		if (c == 27) { break; }
	}

}

```









