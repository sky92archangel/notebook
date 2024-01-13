#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)       #静态库
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       #可执行文件
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       #动态库  需要和可执行文件同目录


#项目名称
PROJECT(jsoncpp_demo)

ADD_SUBDIRECTORY(./src)
 

 

##########################################################################
# #添加程序的子目录mycore  若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
# ADD_SUBDIRECTORY(./mycore)
# #添加程序的子目录mylib   若加EXCLUDE_FROM_ALL则为编译过程忽略该目录
# ADD_SUBDIRECTORY(./mylib)
# #添加程序的子目录mydll   dll到bin中
# ADD_SUBDIRECTORY(./mydll bin)

# #添加程序的子目录src
# ADD_SUBDIRECTORY(./myapp) 