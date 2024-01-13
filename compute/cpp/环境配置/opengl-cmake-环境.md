# OPENGL-CMAKE环境配置

[TOC]



## 前言

首先基本流行操作系统里都自带有部分OPENGL库，但这样还不够，做开发仍然需要其他的库支持，这里主要两个库 GLFW GLAD；
GLAD和GLEW为相近的库，这里使用GLAD；

确保系统中安装了cmake 以及 MinGW编译器  ，当然，若使用完全VS编码则无需MinGW ；

 

## 测试项目文件夹建立

然后建立一个新文件夹，我们建立测试项目

```shell
mkdir opengl_project
cd opengl_project
mkdir lib
mkdir include
mkdir src
mkdir build
touch CMakeLists.txt 
```

首先写好其中CMakeLists.txt 的内容

```cmake
cmake_minimum_required(VERSION 3.2)  #指定最小cmake版本
#指定工程名称
project("opengl_cmake")
#include头文件加载
include_directories("./include/")
#link链接文件加载
link_directories("./lib")

#将整个源码文件夹下的所有c cpp h hpp 文件都纳入 变量src_dir 供后续方便调用
# GLOB全局 RECURSE递归
file(GLOB_RECURSE src_dir 
    "./src/*.cpp" 
    "./src/*.c" 
    "./src/*.hpp" 
    "./src/*.h"
) 
#指定工程的运行代码
#PROJECT_NAME就是上述定义的工程名称
add_executable(${PROJECT_NAME} ${src_dir})

#指定链接文件的名称
target_link_libraries(${PROJECT_NAME} 
glfw3
openGL32
)
```

 

## GLFW

进入GLFW官网

```
https://www.glfw.org/
```

 下载源码，得到文件  glfw-3.3.8.zip  ，解压进入

用命令行打开当前目录

```shell
#建立编译文件夹
mkdir build
#进入文件夹
cd build/
#开始配置编译  这里给出cmake支持的所有选项  
cmake ../ -G 
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

#这里使用 MinGW Makefiles ，若需要使用VS开发 则需要使用 Visual Studio 项了 
cmake ../ -G "MinGW Makefiles"
cmake --build .
	...
	[100%] Built target windows
#此时glfw就编译完成了
#由于此时我们使用MinGW编译，出现的链接库文件为libglfw3.a，位于 glfw_root/build/src/libglfw3.a
 
```



然后做第三方库拷贝

```shell
# 将glfw源码中的 include/GLFW 文件夹拷贝到include中  注意这里最后的斜杠必须要
cp -rf glfw_root/include/GLFW opengl_project/include/
#将上述编译好的库放入lib   注意这里最后的斜杠必须要
cp glfw_root/build/src/libglfw3.a opengl_project/lib/  
```



## GLAD

glad无需编译  较为简单

```shell
#进入glad官网
https://glad.dav1d.de
#语言 Language 选择 C/C++
#特征 Specification 选择 OpenGL
#版本 选择Version 4.6
#Profile 预编译 选择 Compatibility

#下载 得到 glad.zip 解压
#将其中include下文件夹放入 工程的include
cp -rf glad_root/include/glad opengl_project/include/
cp -rf glad_root/include/KHR opengl_project/include/
#将src下的c文件直接放入工程源代码目录下
cp glad_root/src/glad.c opengl_project/lib/
 
```



## 测试代码

在工程代码文件中建立运行主程文件

```shell
cd opengl_project
touch main.cpp
```

主程c++代码

```cpp
#include <iostream>
#include <glad/glad.h>  //这里必须注意 glad的include引用必须位于GLFW前
#include <GLFW/glfw3.h>


int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    if (glfwWindowShouldClose(window))
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*init glad  该动作仅仅使用GLAD才可运行  若为glut或者glew则需要使用其对应的初始化函数*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }
 
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.0f, 0.3f, 0.6f);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    if (glfwWindowShouldClose(window))
    {
        glfwTerminate();
        return -1;
    }

    glfwTerminate();

    return 0;
}
```

然后需要在vscode中使用cmake配置和调试

进vscode

```shell
# ctrl+shift+P 打开 选项   打入 cmake 
# 点击 cmake 调试
```

然后弹出纯色窗口，即为成功；

























