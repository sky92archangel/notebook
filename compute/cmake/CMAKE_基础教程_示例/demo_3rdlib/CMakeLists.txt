#./CMakeLists.txt
cmake_minimum_required(VERSION 3.20)	#指定cmake的版本
project(
	engine						#工程名称
	LANGUAGES CXX C				#可选 编程语言
	DESCRIPTION "GAME ENGINE"	#可选 描述
	VERSION 00.10.00				#可选 版本号
)

# set(EXPORT_COMPILE_COMMANDS ON) #针对ninja makefile等 需要打开
# set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
add_subdirectory(_vendor_)
add_subdirectory(engine)
   
## test
# include(CTest) 		# CTest是cmake官方提供的测试工具集 
# enable_testing()	#启用测试
# add_subdirectory(test)
# add_library(engine STATIC src/main.cpp)  #测试时启用 和add_executable不兼容