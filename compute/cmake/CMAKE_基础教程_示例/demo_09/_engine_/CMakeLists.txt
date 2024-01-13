
# add_executable(_engine_ src/main.cpp)  # 生成时启用和add_library不兼容

add_executable( _engine_ )  # 生成时启用和add_library不兼容 先指定执行者

##############################################

# set_target_properties(_engine_  PROPERTIES
#     WIN32_EXECUTABLE ON #在 Windows 系统中，运行时不启动控制台窗口，只有 GUI 界面 (默认 OFF)
#     LINK_WHAT_YOU_USE ON# 告诉编译器不要自动剔除没有引用符号的链接库 (默认 OFF)
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib#设置动态链接库的输出路径 (默认  ${CMAKE_BINARY_DIR})
#     ARCHIVE OUTPUT DIRECTORY ${CMAKE_SOURCE_DIR}/lib#设置静态链接库的输出路径 (默认  ${CMAKE_BINARY_DIR})
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin#设置可执行文件的输出路径 (默认  ${CMAKE_BINARY_DIR})
#     )

##############################################

#查找目录下匹配的所有文件  
#GLOB_RECURSE递归搜索 文件集合指定为FILE_SRCS   CONFIGURE_DEPENDS为每次config刷新文件
# file(GLOB_RECURSE DIR_SRCS CONFIGURE_DEPENDS 
#     *.cpp 
#     *.hpp 
#     *.h 
#     *.c 
# ) 
aux_source_directory(./src DIR_SRCS) 
target_sources(_engine_ PUBLIC ${DIR_SRCS})  #然后对执行者添加源文件

target_include_directories(_engine_ 
PUBLIC 
	include
	# include/common 
    # ${PROJECT_SOURCE_DIR}/_vendor_/eigen
    # tomlplusplus
) 
 
#将vendor中打包的 Eigen库引入main程序scope
target_link_libraries(_engine_ PUBLIC Eigen)
target_link_libraries(_engine_ PUBLIC Tomlpp)
target_link_libraries(_engine_ PUBLIC Spdlog)


# PRIVATE 头文件搜索路径不会顺延  
# PUBLIC则会扩展顺延  即 B依赖hpp   A依赖B 则 A也可寻得hpp
# INTERFACE 单纯依赖 用于不编译的头文件  纯头文件库可使用
# target一类命令中 前者依赖后者 
target_compile_features(_engine_ PUBLIC cxx_std_17)	#指定语言版本