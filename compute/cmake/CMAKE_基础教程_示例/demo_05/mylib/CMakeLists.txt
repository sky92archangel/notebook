#将当前目录下的所有文件都放入变量DIR_LIB_SRCS内
AUX_SOURCE_DIRECTORY(. DIR_LIB_SRCS) 
 
#指定库文件输出路径 LIBRARY_OUTPUT_PATH    
#PROJECT_BINARY_DIR是cmake产生二进制文件所在路径  即执行cmake的目录 这里是build目录
#将产生的库文件放入固定的成果位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(mymath STATIC ${DIR_LIB_SRCS})

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
#ADD_LIBRARY(libmath SHARED ${DIR_LIB_SRCS})


