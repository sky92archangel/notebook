#将当前目录下的所有文件都放入变量DIR_LIB_SRCS内
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS) 
# set(SRC_LIST 
#         ${DIR_LIB_SRCS}/myprint.cpp
#         ${DIR_LIB_SRCS}/myprint.hpp
#          ) 
# add_executable(DIR_LIB_SRCS ${SRC_LIST})

#指定库文件输出路径 LIBRARY_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将产生的库文件放入固定的成果位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dll)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
# ADD_LIBRARY(mymath STATIC ${DIR_LIB_SRCS})

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(myprint SHARED ${DIR_LIB_SRCS})

# INSTALL(TARGETS myprint ../build/mydll)

# # SET_TARGET_PROPERTIES(myprint PROPERTIES LINKER_LANGUAGE CXX
# #         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
# #         LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
# #         OUTPUT_NAME "myprint"
# #         PREFIX "")

# SET_TARGET_PROPERTIES(myprint PROPERTIES LINKER_LANGUAGE CXX
#         ARCHIVE_OUTPUT_DIRECTORY ../build/mydll
#         LIBRARY_OUTPUT_DIRECTORY ../build/mydll
#         RUNTIME_OUTPUT_DIRECTORY ../build/mydll
#         OUTPUT_NAME "myprint"
#         PREFIX "") 