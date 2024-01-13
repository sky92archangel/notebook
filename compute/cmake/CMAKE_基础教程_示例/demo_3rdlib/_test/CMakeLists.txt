#./CMakeLists.txt
cmake_minimum_required(VERSION 3.20)	#指定cmake的版本
project(
	engine						#工程名称
	LANGUAGES CXX C				#可选 编程语言
	DESCRIPTION "GAME ENGINE"	#可选 描述
	VERSION 0.10.00				#可选 版本号
)

# set(EXPORT_COMPILE_COMMANDS ON) #针对ninja makefile等 需要打开
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
add_subdirectory(3rdlibs)

add_library(engine STATIC src/main.cpp)  #测试时启用 和add_executable不兼容
# add_executable(engine src/main.cpp)  # 生成时启用和add_library不兼容
target_include_directories(engine 
PUBLIC 
include
include/core
)		
# PRIVATE 头文件搜索路径不会顺延  
# PUBLIC则会扩展顺延  即 B依赖hpp   A依赖B 则 A也可寻得hpp
# INTERFACE 单纯依赖 用于不编译的头文件  纯头文件库可使用
# target一类命令中 前者依赖后者 
target_compile_features(engine PUBLIC cxx_std_17)	#指定语言版本

target_link_libraries(engine PUBLIC glfw)

#test
include(CTest) 		# CTest是cmake官方提供的测试工具集 
enable_testing()	#启用测试
add_subdirectory(test)
# add_library(engine STATIC src/main.cpp)  #测试时启用 和add_executable不兼容