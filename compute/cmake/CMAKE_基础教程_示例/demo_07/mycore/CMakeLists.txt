#将当前目录下的所有文件都放入变量DIR_LIB_SRCS内
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS) 
  
#INTERFACE用于纯粹头文件库
ADD_LIBRARY(mycore INTERFACE )
#添加所用文件
target_sources(mycore
PRIVATE
    ${DIR_LIB_SRCS}
)


# #包含core.hpp
# target_include_directories(mycore
# INTERFACE
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )


