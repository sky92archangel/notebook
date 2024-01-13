cmake_minimum_required(VERSION 3.2)
 
# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE "Debug")

#这里对与windows用户非常重要  其解决dll生成后主程仍然寻求lib文件   尤其在于使用MSVC用户
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#生成目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/lib)   	#静态库 静态库编译直接进入exe 这里作为备份
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       	#动态库  需要和可执行文件同目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)       	#可执行文件
 
##############################################
project(IMGUI_DEMO)

add_subdirectory(ImGuiDemoGlad)