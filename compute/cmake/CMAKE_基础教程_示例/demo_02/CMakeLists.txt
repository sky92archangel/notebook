#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
#项目名称
PROJECT(demo4)
#添加程序的子目录mylib   若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
ADD_SUBDIRECTORY(./mylib)
#添加程序的子目录src
ADD_SUBDIRECTORY(./src) 