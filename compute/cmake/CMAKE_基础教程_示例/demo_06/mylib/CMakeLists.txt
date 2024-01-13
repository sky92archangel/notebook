#将当前目录下的所有文件都放入变量DIR_LIB_SRCS内
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#添加静态库 名为libmath.a  静态库文件  linux下为.a   win下为.lib
#STATIC静态库    SHARED动态库  MODULE使用dyld系统有效 否则等同于动态库
# ADD_LIBRARY(mymath STATIC ${DIR_SRCS})
# 建立静态库 mymath  这里应该生成文件mymath.lib 或 mymath.a
ADD_LIBRARY(mymath STATIC)
 
#在这里指定 mymath 的 源代码
target_sources(mymath
PRIVATE
    ${DIR_SRCS}
)
 
# #当前文件夹所有的头文件进入include
# target_include_directories(mymath
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}
# )
 
#所有依赖当前库的使用者 都包含了这里文件  
# 使用者的cmake 文件 只用target_link_libraries连接模块名mymath即可  无需再次使用 target_include_directories 囊括源文件
#建议所有的库都加上该条
target_include_directories(mymath
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# INTERFACE 用于调用者囊括当前库目录   这里就是INTERFACE 
# PUBLIC 用于本库编译时囊括当前库目录 且 调用者囊括当前库目录
# PRIVATE 用于本库编译时囊括当前库目录
# PUBLIC = PRIVATE + INTERFACE