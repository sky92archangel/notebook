
#当前所有目录下的文件放入变量DIR_SRCS
AUX_SOURCE_DIRECTORY(./ DIR_SRCS) 


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_vendor_/jsoncpp/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/_vendor_/jsoncpp/lib/Debug)



#添加可执行程序
# ADD_EXECUTABLE(main main.cpp)
ADD_EXECUTABLE(main ${DIR_SRCS})


#静态lib
TARGET_LINK_LIBRARIES(main
PRIVATE
    jsoncpp.lib
)

# #当前文件夹所有的头文件进入include
# TARGET_LINK_LIBRARIES(main
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}
# )