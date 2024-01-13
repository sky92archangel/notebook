
#当前所有目录下的文件放入变量DIR_SRCS
AUX_SOURCE_DIRECTORY(./ DIR_SRCS) 

#添加可执行程序
ADD_EXECUTABLE(main main.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_vendor_/)


# #当前文件夹所有的头文件进入include
# TARGET_LINK_LIBRARIES(main
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}
# )