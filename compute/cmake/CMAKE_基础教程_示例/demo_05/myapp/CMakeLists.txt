#向工程添加多个头文件搜索路径  PROJECT_SOURCE_DIR 项目根目录路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mylib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mydll)

#指定可执行文件输出路径 EXECUTABLE_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将生成的可执行文件放入固定的成果位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#将当前目录下的所有文件都放入变量DIR_SRCS内
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

#添加可执行程序
ADD_EXECUTABLE(demo5 ${DIR_SRCS})

#将子目录生成的库链接过来
TARGET_LINK_LIBRARIES(demo5 mymath)
TARGET_LINK_LIBRARIES(demo5 myprint) 