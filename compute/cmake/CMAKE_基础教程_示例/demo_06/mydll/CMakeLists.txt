#将当前目录下的所有文件都放入变量DIR_LIB_SRCS内
AUX_SOURCE_DIRECTORY(. DIR_SRCS)  

#添加动态库 名为libmath.so  动态库文件  linux下为.so   win下为.dll
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
ADD_LIBRARY(myprint SHARED ${DIR_SRCS})
  

#所有依赖当前库的使用者 都包含了这里文件     
#使用者的cmake文件 只用target_link_libraries连接模块名mymath即可  可直接囊括调用当前库源文件
#使用者的cmake文件无需再次使用 target_include_directories 来囊括源文件
#建议所有的库都加上该条  
target_include_directories(myprint
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE