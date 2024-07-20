# CMAKE 教程

[TOC]

## 零、GCC命令

对于写好的c语言文件 main.c

### 1.直接生成可执行文件：

```shell
#直接生成可执行文件
gcc main.c -o main 
#多个文件
gcc main.c fun.c -o main 
```

### 2.分步操作：

预处理、编译、汇编、链接

可对多文件名分别处理到 .o 文件 

```shell
#预处理  	结果main.i文件
gcc -E main.c -o main.i

#编译器	编译后文件main.s
gcc -S main.i

#汇编器	继续汇编产生main.o文件
gcc -c main.s 

#链接器 	将main.o文件链接起来 产生main可执行文件
gcc main.o -o main
```



## 一、Makefile

### 1.例子

若工程编译过，仅仅编译修改的文件或头文件引用的所有内容 Makefile

主要缩行必须用TAB

```makefile
main : main.o input.o calcu.o  
	gcc -o main main.o input.o calcu.o 
main.o：main.c
	gcc -c main.c
input.o：input.c
	gcc -c input.c
calcu.o：calcu.c
	gcc -c calcu.c	

clean:
	rm *.o
	rm main
```

### 2.变量和赋值

主要缩行必须用TAB

引用makeflie变量

```makefile
#Makefile变量使用
objects = main.o input.o 
main:$(objects)
	gcc -o main $(objects)
main.o：main.c
	gcc -c main.c
input.o：input.c
	gcc -c input.c
calcu.o：calcu.c
	gcc -c calcu.c	

clean:
	rm *.o
	rm main
```

= 号为类似指针的赋值 变量会接受最后一次赋的值

```makefile
name = zdk
curname = $(name)
name = tre

#name更新后影响了curname的值 故=号类似于传递指针 
#此处打印为 echo curname:tre    @符号为在shell命令行显示执行过程  不加则显示curname:tre
print:
	@echo curname:$(curname)
```

:=为创建一个新对象

```makefile
name = zdk
curname := $(name)
name = tre

#name更新后影响了curname的值 故:=号类似于创建新副本 
#此处打印为 echo curname:zdk    @符号为在shell命令行显示执行过程  不加则显示curname:zdk
print:
	@echo curname:$(curname)
```

?= 检测变量是否赋值  若没有  则赋值  否则不动

+= 对变量追加内容

### 3.模式规则

将c文件编译为o

%类似通配符  

自动化变量

```makefile
 $@ 
 $< 自动匹配依赖
 $^
```

原有文件改写为

```makefile
#Makefile
objects = main.o input.o 
main:$(objects)
	gcc -o main $(objects)
#自动匹配依赖
%.o：%.c
	gcc -c  $< 
	
clean:
	rm *.o
	rm main
```

伪目标，无论当前目录下是否有clean名字的文件 都进行makefile里默认的clean操作

```makefile
.PHONY:clean
```

条件判断

```makefile
【条件判断字】
	【真时执行】
else
	【假时执行】
endif
```

## 二、CMakeLists编写

**每个目录下都会有CMakeLists.txt**



### 1.指定编译器和参数

```cmake
#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)   

##########指定编译器#########
#若想指定编译器则需要如下内容    注意必须在CMAKE_MINIMUM_REQUIRED之后指定
#指定C编译器
set (CMAKE_C_COMPILER "/path_to_gcc/gcc")
#指定C++编译器
set (CMAKE_CXX_COMPILER "/path_to_gpp/g++")
#如不指定则使用系统默认编译器

#########设置编译模式######### 
set(CMAKE_BUILD_TYPE Debug)
# Debug:包含调试信息，不进行优化 
# Release:不包含调试信息，进行优化 
# RelWithDeblnfo:包含调试信息，并进行优化 
# MinSizeRel:尽可能减小生成文件的大小
# 也可以命令时决定 cmake-S.-B build -DCMAKE_BUILD_TYPE=Debug


#########添加编译参数#########
#设置编译选项（配置编译器）有如下三种方法
#ADD_COMPILE_OPTIONS方法会递归引用到整个项目中 针对所有编译器
ADD_COMPILE_OPTIONS(-std=c++11 -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)
#ADD_DEFINITIONS方法会递归引用到整个项目中 针对所有编译器
ADD_DEFINITIONS(-std=c++11 -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)
#set命令设置CMAKE_C_FLAGS只针对c编译器
SET(CMAKE_C_FLAGS  -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)
```



### 2.find_package用法

```cmake
#一般这样引用 LZ4压缩算法 
find_package(LZ4 ) 
# REQUIRED 指找不到就报错
find_package(LZ4 REQUIRED)
# 如果只需要XXX组件
find_package(LZ4 COMPONENTS xxx)
# 直接给出路径
find_package(PackageName [PATHS path1 [path2 ... ]])

# 除了直接指定路径外，其他方法都需要将这个库加入CMAKE的查询路径中 cmake默认查找位置为根目录的//.../cmake/module/Findxxx.cmake
# 那么有两种方法解决这个问题
# 1 在cmake的module增加一个findxxx.cmake 文件
# 2 在当前项目下新建cmake文件夹，在其目录下新增findxxx.cmake文件

#######如果想opengl这种常用系统都具有的库直接link即可
find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)
```

代码示例

```cmake
set(CMAKE_CXX_STANDARD 11)
add_executable(lz4_exe lz4.cpp)
#cmake default search path for external libraries
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(LZ4 REQUIRED) 
# //cmake/module/Findxxx.cmake
if(LZ4_FOUND)
    target_include_directories(lz4 exe PRIVATE ${LZ4_INCLUDE_DIR})
    target_link_libraries(lz4_exe PRIVATE ${LZ4_LIBRARY})
else()
    message(FATAL_ERROR "LZ4 library not found.")
endif()
```

上述示例中，有用户无法找到LZ4包

因为需要将这个库加入CMAKE的查询路径中 cmake默认查找位置为根目录的//.../cmake/module/Findxxx.cmake
那么有两种方法解决这个问题:
1 在cmake的module增加一个findxxx.cmake 文件
2 在当前项目下新建cmake文件夹，在其目录下新增findxxx.cmake文件，当然这样的话需要在CMakeLists.txt中增加一行

```cmake
# CMAKE_MODULE_PATH 为cmake第三方库路径
# CMAKE_CURRENT_SOURCE_DIR为当前CMakeLists.txt所在文件路径
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
```



下面是.cmake的写法

FindLz4.cmake

```cmake
#查询头文件
find_path(LZ4_INCLUDE_DIR Lz4.h /path_to_lz4/include ${CMAKE_SOURCE_DIR}/ModulesMode
#查询动态库
find_library(LZ4_LIBRARY NAMES LZ4 PATHS /path_to_lz4/lib ${CMAKE_SOURCE_DIR}/Modules
message(STATUS "enter cmake directory!")

if(LZ4_INCLUDE_DIR AND LZ4_LIBRARY)
    set(LZ4_FOUND TRUE)
endif(LZ4_INCLUDE_DIR AND LZ4_LIBRARY)
```



### 3.引用vcpkg管理的库

```shell
#直接定位vcpkg的cmake文件
cmake -B [build directory]-S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
#或者直接将 这个路径 path to vcpkg]/scripts/buildsystems/vcpkg.cmake 加入到系统路径
#  CMAKE_TOOLCHAIN_FILE   vcpkg]/scripts/buildsystems/vcpkg.cmake
#同时推荐指定 VCPKG_DEFAULT_TRIPLET 为 x64-windows  为安装时默认版本
#  VCPKG_DEFAULT_TRIPLET    x64-windows 
```



### 4.搭配vcpkg的manifest模式自动配置

该配置采用config模式

vcpkg.json

```json
{
    "name": "opengl",
    "version":"0.0.1",
    "description":"learn the OpenGL",
    "dependencies":[
            "eigen3",
            "imgui",
            "glfw3",
            "glm",
            "glad",
            "assimp"
        ]
}
```

CMakeLists.txt

```cmake
find_package(imgui CONFIG REQUIRED )
target_link_libraries(main PRIVATE imgui::imgui)
```



### 5.闭源库或已编译库

```CMAKE
# IMPORTED
# 采用已经编译的 glfw 库为例

cmake_minimum_required(VERSION 3.20)
project(tryIMPORTED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REOUIRED ON)

add_executable(main main.cpp)

add_library(glfw STATIC IMPORTED)
set_property(TARGET glfw PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/lib-vc2019/glfw3.lib)
#已编译库必须采用INTERFACE
target_include_directories(glfw INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw/include)

target_link_libraries(main glfw)

```





## 三、示例

### 1.单文件单文件demo1

单文件

```cmake
#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)   
#项目名称
PROJECT(demo1)	
#添加可执行程序
ADD_EXECUTABLE(demo1 power.cpp)
```

在不同系统有不同表现

将CMakeLists.txt翻译为当前系统的Makeflie （针对VS编译器会出现一个sln及相关文件）

```shell
cmake ./
```

linux下

```shell
make 
```

win下 直接打开sln操作

### 2.单目录多文件demo2

多文件

```cmake
#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

#项目名称
PROJECT(demo2)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)  

#添加可执行程序
ADD_EXECUTABLE(demo2 ${DIR_SRCS})
```

### 3.多目录多文件demo3

多目录多文件目录结构

```shell
.
├── CMakeLists.txt
├── main.cpp
└── mylib
    ├── CMakeLists.txt
    ├── mymath.cpp
    └── mymath.hpp
```

子目录mylib的CMakeLists.txt 

```cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS) 

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(libmath.a STATIC ${DIR_LIB_SRCS})

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(libmath.so SHARED ${DIR_LIB_SRCS})
```

主程目录的CMakeLists.txt 

```cmake
#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

#项目名称
PROJECT(demo3)

#添加程序的子目录 即考虑子目录下的CMakeLists.txt  若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mylib)

# 查找当前目录下的所有源文件 但只能找一层 无法嵌套寻找
# 并将名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(./ DIR_SRCS) 

#添加可执行程序
ADD_EXECUTABLE(demo3 ${DIR_SRCS})

#将子目录生成的库链接过来
TARGET_LINK_LIBRARIES(demo3 libmath.a)
```

### 4.标准工程demo4

目录结构

```
.
├── build
├── CMakeLists.txt
├── mylib
│   ├── CMakeLists.txt
│   ├── mymath.cpp
│   └── mymath.hpp
└── src
    ├── main.cpp
    └── CMakeLists.txt
```

src 的 CMakeLists.txt  主要任务 ：查找头文件  添加主程依赖 引用库文件

```cmake
#向工程添加多个头文件搜索路径 
#PROJECT_SOURCE_DIR 最近的包含PROJECT关键词的CMakeLists.txt所在的路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mylib)

#指定可执行文件输出路径 EXECUTABLE_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将生成的可执行文件放入固定的成果位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

#添加可执行程序
ADD_EXECUTABLE(demo4 ${DIR_SRCS})

#将子目录生成的库链接过来
TARGET_LINK_LIBRARIES(demo4 libmath.a)
```

mylib的 CMakeLists.txt  主要任务：生成库文件

```cmake
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)

#指定库文件输出路径 LIBRARY_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将产生的库文件放入固定的成果位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(libmath.a STATIC ${DIR_LIB_SRCS})

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(libmath.so SHARED ${DIR_LIB_SRCS})

###############注意这里的ADD_LIBRARY只能存在一个 一份代码的静态库和动态库只能生成一种
```

工程根目录的 CMakeLists.txt  统筹各个子目录

```cmake
#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

#项目名称
PROJECT(demo4)

#添加程序的子目录mylib 考虑子目录下的CMakeLists.txt 若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mylib)

#添加程序的子目录src   考虑子目录下的CMakeLists.txt
ADD_SUBDIRECTORY(./src) 
```

### 5.标准工程demo5

文件夹结构

```SHELL
.
├── CMakeLists.txt
├── myapp
│   ├── CMakeLists.txt
│   └── main.cpp
├── mydll
│   ├── CMakeLists.txt
│   ├── myprint.cpp
│   └── myprint.hpp
└── mylib
    ├── CMakeLists.txt
    ├── mymath.cpp
    └── mymath.hpp 
```

windows中的注意事项

```c++
//这里的需要生成dll文件的工程代码务必注意一点 
//在windows中  所有的类和函数前都要加上  __declspec(dllexport) 前缀  此前缀可以用宏定义来简化写法
//这样才能调用封装在动态链接库中的函数
//==================================myprint.hpp======================================
#define MY_LIB_API __declspec(dllexport) 
#include<iostream>
#include<string>
inline
void MY_LIB_API myprint(std::string str1, double count);
```

./mydll/CMakeLists.txt  动态库代码   主要任务：生成动态库文件

```cmake
##########################  ./mydll/CMakeLists.txt    #############################

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS)  

#指定库文件输出路径 LIBRARY_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将产生的库文件放入固定的成果位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dll)
 
#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(myprint SHARED ${DIR_LIB_SRCS})
```

./mylib/CMakeLists.txt  静态库代码  主要任务：生成静态库文件

```cmake
##########################  ./mylib/CMakeLists.txt    #############################

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS) 
 
#指定库文件输出路径 LIBRARY_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将产生的库文件放入固定的成果位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(mymath STATIC ${DIR_LIB_SRCS})
  
```

./myapp/CMakeLists.txt   主程的 CMakeLists.txt     主要任务 ：查找头文件  添加主程依赖 引用库文件

```cmake
##########################  ./myapp/CMakeLists.txt    #############################
#向工程添加多个头文件搜索路径  PROJECT_SOURCE_DIR 项目根目录路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mylib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mydll)

#指定可执行文件输出路径 EXECUTABLE_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将生成的可执行文件放入固定的成果位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#将当前目录下的所有文件都放入变量DIR_SRCS内
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

#添加可执行程序
ADD_EXECUTABLE(demo5 ${DIR_SRCS})

#将子目录生成的库链接过来
TARGET_LINK_LIBRARIES(demo5 mymath)
TARGET_LINK_LIBRARIES(demo5 myprint) 
```

./CMakeLists.txt     工程根目录的 CMakeLists.txt  统筹各个子目录

```cmake
##########################  ./CMakeLists.txt    #############################

#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#项目名称
PROJECT(demo5)

#添加程序的子目录mylib   若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mylib)
#添加程序的子目录mydll 且将上面所得到的myprint.lib以及myprint.dll复制并放到bin文件夹中
ADD_SUBDIRECTORY(./mydll bin)

#添加程序的子目录src
ADD_SUBDIRECTORY(./myapp) 
```



### 6.改进demo5标准工程demo6 

文件夹结构

```SHELL
.
├── CMakeLists.txt
├── myapp
│   ├── CMakeLists.txt
│   └── main.cpp
├── mydll
│   ├── CMakeLists.txt
│   ├── myprint.cpp
│   └── myprint.hpp
└── mylib
    ├── CMakeLists.txt
    ├── mymath.cpp
    └── mymath.hpp 
```

windows中的注意事项

```c++
//这里的需要生成dll文件的工程代码务必注意一点 
//在windows中  所有的类和函数前都要加上  __declspec(dllexport) 前缀  此前缀可以用宏定义来简化写法
//这样才能调用封装在动态链接库中的函数
//==================================myprint.hpp======================================
#define MY_LIB_API __declspec(dllexport) 
#include<iostream>
#include<string>
inline
void MY_LIB_API myprint(std::string str1, double count);
```

./mydll/CMakeLists.txt  动态库代码   主要任务：生成动态库文件

```cmake
##########################  ./mydll/CMakeLists.txt    #############################

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_SRCS)  

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(myprint SHARED ${DIR_SRCS})
  
#所有依赖当前库的使用者 都包含了这里文件   INTERFACE 关键字用法  
#使用者的cmake文件 只用target_link_libraries连接模块名mymath即可  可直接囊括调用当前库源文件
#使用者的cmake文件无需再次使用 target_include_directories 来囊括源文件
#建议所有的库都加上该条
target_include_directories(myprint
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE
```

./mylib/CMakeLists.txt  静态库代码  主要任务：生成静态库文件

```cmake
##########################  ./mylib/CMakeLists.txt    #############################

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
# 建立静态库 mymath  这里应该生成文件mymath.lib 或 mymath.a
ADD_LIBRARY(mymath STATIC)
 
#在这里指定 mymath 的 源代码
target_sources(mymath
PRIVATE
    ${DIR_SRCS}
)
  
#所有依赖当前库的使用者 都包含了这里文件   INTERFACE 关键字用法  
#使用者的cmake文件 只用target_link_libraries连接模块名mymath即可  可直接囊括调用当前库源文件
#使用者的cmake文件无需再次使用 target_include_directories 来囊括源文件
#建议所有的库都加上该条
target_include_directories(mymath
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE
```

./myapp/CMakeLists.txt   主程的 CMakeLists.txt     主要任务 ：查找头文件  添加主程依赖 引用库文件

```cmake
##########################  ./myapp/CMakeLists.txt    #############################

#向工程添加多个头文件搜索路径  PROJECT_SOURCE_DIR 项目根目录路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mylib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mydll)
  
# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

#添加可执行程序
ADD_EXECUTABLE(demoproj6 ${DIR_SRCS})

#将子目录生成的库链接过来
TARGET_LINK_LIBRARIES(demoproj6 
PRIVATE
    mymath
    myprint
) 
```

./CMakeLists.txt     工程根目录的 CMakeLists.txt  统筹各个子目录

```cmake
##########################  ./CMakeLists.txt    #############################

#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/lib)   #静态库 静态库编译直接进入exe 这里作为备份
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       #可执行文件
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       #动态库  需要和可执行文件同目录

#项目名称
PROJECT(demoproj6)

#添加程序的子目录mylib   若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mylib)
#添加程序的子目录mydll  动态库  若上述不指定输出则写为  ADD_SUBDIRECTORY(./mydll bin)
ADD_SUBDIRECTORY(./mydll)

#添加程序的子目录src  这里是主程文件夹
ADD_SUBDIRECTORY(./myapp) 
```

构建和编译

```shell
#直接指定configuration的文件夹为build
$ cmake -B build
# 开始构建
cmake --build build/
#此时在 build文件夹内就出现了结果  当然结果文件结构会根据CMakeLists.txt内的设置有改变  
#这里结果应该是出现连个文件夹 bin build 
```

  

### 附

```cmake
#这里对与windows用户非常重要  其解决dll生成后主程仍然寻求lib文件   尤其在于使用MSVC用户
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#创建工程helloworld
PROJECT (helloworld)

#将源文件作为变量src
SET(src  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ) 
	
#添加可执行程序 helloworld工程 为目标
ADD_EXECUTABLE(helloworld   ${src})

#################生成完成后进行的动作###############################
#完成或者开始编译一个目标前，执行某些命令（例如拷贝，自动生成.in文件等）
add_custom_command(
		#指定名为${PROJECT_NAME}的目标，在它编译完成之后执行命令
        TARGET ${PROJECT_NAME}  POST_BUILD 
        #要执行的命令名字为 ${CMAKE_COMMAND} -E代表的是环境无关的文件操作 copy_directory是拷贝文件夹
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        #指定从哪拷贝到哪。这里是把build/Release拷贝到当前目录
        ${CMAKE_BINARY_DIR}/$<CONFIGURATION> ${CMAKE_CURRENT_LIST_DIR}
        )
        
# COPY的语法是： file(COPY <填写你要拷贝的文件> DESTINATION <填写你要的输出目录>)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/udp/udp_interface.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/publish/x64/include)
```



## 四、CMAKE命令

### 1.cmake基础命令

```shell

#假设已经完成了所有的CMakeLists.txt的编写
################################################
#进入项目根目录 建立build文件夹 
$ mkdir build
#进入build
$ cd build
# 开始构建
$ cmake ..
# 开始构建
cmake --build .
#此时在 build文件夹内就出现了结果  当然结果文件结构会根据CMakeLists.txt内的设置有改变
################################################
#当然可以不进入build文件夹 
#直接指定configuration的文件夹为build
$ cmake -B build
# 开始构建
cmake --build build/
#此时在 build文件夹内就出现了结果  当然结果文件结构会根据CMakeLists.txt内的设置有改变
```

 

### 2.cmake命令行指定编译器

```shell
#可以直接输入，可以看到当前版本支持的编译器
$ cmake -G
CMake Error: No generator specified for -G

Generators
* Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
  Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 10 2010 [arch] = Deprecated.  Generates Visual Studio 2010
                                 project files.  Optional [arch] can be
                                 "Win64" or "IA64".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Borland Makefiles            = Generates Borland makefiles.
  NMake Makefiles              = Generates NMake makefiles.
  NMake Makefiles JOM          = Generates JOM makefiles.
  MSYS Makefiles               = Generates MSYS makefiles.
  MinGW Makefiles              = Generates a make file for use with
                                 mingw32-make.
  Green Hills MULTI            = Generates Green Hills MULTI files
                                 (experimental, work-in-progress).
  Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  CodeBlocks - MinGW Makefiles = Generates CodeBlocks project files.
  CodeBlocks - NMake Makefiles = Generates CodeBlocks project files.
  CodeBlocks - NMake Makefiles JOM
                               = Generates CodeBlocks project files.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - MinGW Makefiles   = Generates CodeLite project files.
  CodeLite - NMake Makefiles   = Generates CodeLite project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Eclipse CDT4 - NMake Makefiles
                               = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - MinGW Makefiles
                               = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
  Kate - MinGW Makefiles       = Generates Kate project files.
  Kate - NMake Makefiles       = Generates Kate project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Sublime Text 2 - MinGW Makefiles
                               = Generates Sublime Text 2 project files.
  Sublime Text 2 - NMake Makefiles
                               = Generates Sublime Text 2 project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files.

# Visual Studio 编译器
$ cmake -S . -B build -G "Visual Studio 17 2022"

#windows下nmake支持
cmake -S . -B build -G "NMake Makefiles"

#Ninja  安卓和鸿蒙方案
cmake -S . -B build -G Ninja

#windows下g++ MinGW支持
cmake -S . -B build -G "MinGW Makefiles"
```

 

### 3.指定编译模式

```shell
cmake-S.-B build -DCMAKE_BUILD_TYPE=Debug

# cmake内部也可以设置编译模式 
set(CMAKE_BUILD_TYPE Debug)
# Debug:包含调试信息，不进行优化 
# Release:不包含调试信息，进行优化 
# RelWithDeblnfo:包含调试信息，并进行优化 
# MinSizeRel:尽可能减小生成文件的大小
```





## 五、cmake配置文件

当需要引入cmake脚本模块配置的时候

```cmake
######################  针对 ./cmakeconf/building_output.cmake  ####################
INCLUDE(cmakeconf/building_output.cmake)

######################  针对 ./cmakeconf/compiler_conf.cmake  ####################
INCLUDE(cmakeconf/compiler_conf.cmake)

#这两个语句放入同目录CMakeLists即可

#更加简单的写法  版本3.15+
SET(CMAKE_MODULE_PATH   ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmakeconf )
INCLUDE(building_output)
INCLUDE(compiler_conf)
```

生成选项

```cmake
# 设置C/C++标准 生成配置
add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -03 -Wall")
```

 



## 附录1 完整示例工程

### 目录部分

```shell
.
├── CMakeLists.txt 
├── myapp
│   ├── CMakeLists.txt
│   └── main.cpp
├── mycore
│   ├── CMakeLists.txt
│   └── core.cpp
├── mydll
│   ├── CMakeLists.txt
│   ├── myprint.cpp
│   └── myprint.hpp
└── mylib
    ├── CMakeLists.txt
    ├── mymath.cpp
    └── mymath.hpp 
```

### 代码部分

windows中的注意事项

```c++
//这里的需要生成dll文件的工程代码务必注意一点 
//在windows中  所有的类和函数前都要加上  __declspec(dllexport) 前缀  此前缀可以用宏定义来简化写法
//这样才能调用封装在动态链接库中的函数
//==================================myprint.hpp======================================
#define MY_LIB_API __declspec(dllexport) 
#include<iostream>
#include<string>
inline
void MY_LIB_API myprint(std::string str1, double count);
```

main.cpp

```C++
#include <iostream>
#include <stdlib.h>
#include "mymath.hpp"
#include "myprint.hpp"
// #include "../mylib/mymath.hpp"
// using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage:" << argv[0] << std::endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exp = atoi(argv[2]);
    std::cout << "result:" << std::endl
              << power(base, exp);

    myprint("result is ", power(base, exp));
#if DEBUG
    std::cout << " DEBUG ON " << std::endl;
#endif
    return 0;
}
```

./mylib/mymath.hpp

```c++
#pragma once 
inline 
double power(double base, double exp); 
```

./mylib/mymath.cpp

```c++
#include "mymath.hpp"
double power(double base , double exp)
{
    int res = base;
    if(base ==1)
    {
        return 1;
    }
    for (int i = 1; i < exp; i++)
    {
        res = res*base;
    }
    return res;
}
```

./mydll/myprint.hpp

```c++
#pragma once

#include "core.hpp"
#include <iostream>
#include <string>
 
inline 
void API_EXPORT myprint(std::string str1, double count);

```

./mydll/myprint.cpp

```c++

#include "myprint.hpp"

void MY_LIB_API myprint(std::string str1, double calResult)
{
    std::cout << str1 << calResult << std::endl;
}
```

./mycore/core.hpp

```c++
#define API_IMPORT __declspec(dllimport)//如果是生成使用dll的工程，那么导入
#define API_EXPORT __declspec(dllexport)//如果是生成dll工程，那么导出 
```

### CMake文件部分

 ./mycore/CMakeLists.txt  动态库代码   主要任务：纯粹头文件库提供给其他程序引用

```cmake
#将当前目录下的所有文件都放入变量DIR_LIB_SRCS内
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS) 
  
#INTERFACE用于纯粹头文件库
ADD_LIBRARY(mycore INTERFACE )
#添加所用文件
target_sources(mycore
PRIVATE
    ${DIR_LIB_SRCS}
)

#所有依赖当前库的使用者 都包含了这里文件   INTERFACE 关键字用法  
#使用者的cmake文件 只用target_link_libraries连接模块名mycore即可  可直接囊括调用当前库源文件
#使用者的cmake文件无需再次使用 target_include_directories 来囊括源文件
#建议所有的库都加上该条  虽然不一定起效用  
# 将自己的头文件供给其他调用  
#包含core.hpp  
target_include_directories(mycore
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE
```



./mydll/CMakeLists.txt  动态库代码   主要任务：生成动态库文件

```cmake
##########################  ./mydll/CMakeLists.txt    #############################

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_SRCS)  

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(myprint SHARED ${DIR_SRCS})
  
#所有依赖当前库的使用者 都包含了这里文件   INTERFACE 关键字用法  
#使用者的cmake文件 只用target_link_libraries连接模块名mymath即可  可直接囊括调用当前库源文件
#使用者的cmake文件无需再次使用 target_include_directories 来囊括源文件
#建议所有的库都加上该条 虽然不一定起效用   即将自己的头文件供给其他调用
target_include_directories(myprint
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE

#这里的myprint 依赖 mycore
TARGET_LINK_LIBRARIES(myprint
PUBLIC
    mycore  
) 
 
```

./mylib/CMakeLists.txt  静态库代码  主要任务：生成静态库文件

```cmake
##########################  ./mylib/CMakeLists.txt    #############################

# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
# 建立静态库 mymath  这里应该生成文件mymath.lib 或 mymath.a
ADD_LIBRARY(mymath STATIC)
 
#在这里指定 mymath 的 源代码
target_sources(mymath
PRIVATE
    ${DIR_SRCS}
)
  
#所有依赖当前库的使用者 都包含了这里文件   INTERFACE 关键字用法  
#使用者的cmake文件 只用target_link_libraries连接模块名mymath即可  可直接囊括调用当前库源文件
#使用者的cmake文件无需再次使用 target_include_directories 来囊括源文件
#建议所有的库都加上该条
target_include_directories(mymath
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE
```

./myapp/CMakeLists.txt   主程的 CMakeLists.txt     主要任务 ：查找头文件  添加主程依赖 引用库文件

```cmake
##########################  ./myapp/CMakeLists.txt    #############################

#向工程添加多个头文件搜索路径  PROJECT_SOURCE_DIR 项目根目录路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mycore)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mylib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mydll)
  
# 查找当前目录下的所有源文件  并将所有文件名称保存到 DIR_SRCS 变量
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

#添加可执行程序
ADD_EXECUTABLE(demoproj7 ${DIR_SRCS})

#将子目录生成的库链接过来  这里最好注意顺序  越是基础越是先放
TARGET_LINK_LIBRARIES(demoproj7 
PRIVATE
	mycore
    mymath
    myprint
) 
```

./CMakeLists.txt     工程根目录的 CMakeLists.txt  统筹各个子目录

```cmake
##########################  ./CMakeLists.txt    #############################

#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#这里对与windows用户非常重要  其解决dll生成后主程仍然寻求lib文件   尤其在于使用MSVC用户
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/lib)   #静态库 静态库编译直接进入exe 这里作为备份
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       #可执行文件
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       #动态库  需要和可执行文件同目录

#项目名称
PROJECT(demoproj7)


#添加程序的子目录mycore 若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mycore)
#添加程序的子目录mydll  动态库  若上述不指定输出则写为  ADD_SUBDIRECTORY(./mydll bin)
ADD_SUBDIRECTORY(./mydll)
#添加程序的子目录mylib   若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mylib)


#添加程序的子目录src  这里是主程文件夹
ADD_SUBDIRECTORY(./myapp) 
```

构建和编译

```shell
#直接指定configuration的文件夹为build
$ cmake -B build
# 开始构建
$ cmake --build build/
#此时在 build文件夹内就出现了结果  当然结果文件结构会根据CMakeLists.txt内的设置有改变  
#这里结果应该是出现连个文件夹 bin build 
```

 

## 实例二

### 工程1

工程目录

```shell
.
├── CMakeLists.txt
├── include
│   ├── core
│   │   ├── assert.hpp
│   │   ├── cgmath.hpp
│   │   └── log.hpp
│   └── engine.hpp
├── src
│   └── main.cpp
└── test
    ├── catch.hpp
    ├── cgmath.hpp
    └── CMakeLists.txt
```

./CMakeLists.txt

```cmake
#./CMakeLists.txt
cmake_minimum_required(VERSION 3.20)	#指定cmake的版本
project(
	engine						#工程名称
	LANGUAGES CXX C				#可选 编程语言
	DESCRIPTION "GAME ENGINE"	#可选 描述
	VERSION 0.10.00				#可选 版本号
)

set(EXPORT_COMPILE_COMMANDS ON) #针对ninja makefile等 需要打开
set (CMAKE_EXPORT_COMPILE_COMMANDS ON) #针对ninja makefile 正规写法 需要打开
 
# add_library(engine STATIC src/main.cpp)  #测试专用 和add_executable不兼容
add_executable(main src/main.cpp)
target_include_directories(main 
PUBLIC 
	include
	include/core
)		

# PRIVATE 头文件搜索路径不会顺延  
# PUBLIC则会扩展顺延 
# INTERFACE 单纯依赖 用于不编译的头文件
# target一类命令中 前者依赖后者 
target_compile_features(main PUBLIC cxx_std_17)	#指定语言版本

include(CTest) 		# CTest是cmake官方提供的测试工具集 
enable_testing()	#启用测试
add_subdirectory(test)
```

cmake编译命令

```shell
##########初始化指令##########
#S指定camke初始化目录  B指定cmake构建路径
$ cmake -S . -B cmake-build

#可以直接输入，可以看到当前版本支持的编译器  带有*号为默认
$ cmake -G
CMake Error: No generator specified for -G
Generators
* Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
  Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
                                 ...
#所以初始化的命令我们也可以这样写
$ cmake -S . -B cmake-build -G "Visual Studio 17 2022"
#默认PC首编译器 如果时VS2022 则会出现cmake-build目录，并在其中出现sln工程

##########编译指令##########
$ cmake --build ./cmake-build/

```

./test/CMakeLists.txt

```cmake
add_executable(cgmath ./cgmath.cpp)		#添加文件

#构建测试工程 TARGET_FILE表达测试文件的生成运行路径
add_test(NAME cgmath_test COMMAND $<TARGET_FILE:cgmath>)	

#先前在主CAMKE文件engine内add_library指定的库   前者依赖后者
target_link_libraries(cgmath  PRIVATE  engine)
```



































