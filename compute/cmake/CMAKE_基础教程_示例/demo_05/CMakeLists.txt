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
#添加程序的子目录mydll
ADD_SUBDIRECTORY(./mydll bin)

#添加程序的子目录src
ADD_SUBDIRECTORY(./myapp) 