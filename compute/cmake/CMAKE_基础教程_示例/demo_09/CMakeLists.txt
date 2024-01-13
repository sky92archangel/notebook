#./CMakeLists.txt
cmake_minimum_required(VERSION 3.22)	#指定cmake的版本

#本段定义语言 建议放在project之前使用
set(CMAKE_CXX_STANDARD 17)  #使用c++17标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
#  cmake针对msvc时 为了防止GCC参杂自身特性-std=gnu++17  故OFF
 
#建立工程
project(
	_engine_						#工程名称
	LANGUAGES  NONE					#可选 编程语言  可暂为空
	DESCRIPTION "GAME_ENGINE"		#可选 描述
	HOMEPAGE_URL https://www.bilibili.com #主页
	VERSION 01.02.03				#可选 版本号
)
enable_language(C)					#启用C语言
enable_language(CXX)				#启用CXX语言

#设置编译模式为Debug   常用选项Debug Release MinSizeRel RelWithDebInof
set(CMAKE_BUILD_TYPE Debug)
#若编译模式为Release
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
# set(EXPORT_COMPILE_COMMANDS ON) #针对ninja makefile等 需要打开
# set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

#windows 的 MINMAX的宏定义控制
if(WIN32)
	add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

add_subdirectory(_vendor_)
add_subdirectory(_engine_)
   
## test
# include(CTest) 		# CTest是cmake官方提供的测试工具集 
# enable_testing()	#启用测试
# add_subdirectory(test)
# add_library(engine STATIC src/main.cpp)  #测试时启用 和add_executable不兼容
 

#打印工程描述
message("PROJECT_NAME: ${PROJECT_NAME}")						#工程名
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}") 			#最近一次调用project的cmake目录
message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")#当前cmake目录
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message("PROJECT_IS_TOP_LEVEL: ${PROJECT_IS_TOP_LEVEL}")	#当前项目是否顶层根目录


#打印版本号 project中定义VERSION来决定
message("PROJECT_NAME : ${PROJECT_NAME}")					#工程名
message("PROJECT_VERSION : ${PROJECT_VERSION}")				#全版本号
message("PROJECT_VERSION_MAJOR: ${PROJECT_VERSION_MAJOR}")	#主版本
message("PROJECT_VERSION_MINOR: ${PROJECT_VERSION_MINOR}")	#次版本
message("PROJECT_VERSION_PATCH: ${PROJECT_VERSION_PATCH}")	#补丁版本
message("_engine__VERSION: ${_engine__VERSION}")

