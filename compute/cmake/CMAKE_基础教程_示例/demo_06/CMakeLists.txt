#指定最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置C/C++标准 生成配置
add_definitions(-std=c++17)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -03 -Wall")

#生成目录
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


#根据模块名称查找依赖库
# find_package(Vulkan REQUIRED)
# if(Vulkan_FOUND)
#     message("vulkan found ${Vulkan_INCLUDE_DIRS} ${Vulkan_LIBRARIES} ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE}")
# endif(Vulkan_FOUND)
 