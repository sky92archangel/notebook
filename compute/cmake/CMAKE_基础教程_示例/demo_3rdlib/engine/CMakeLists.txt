
add_executable(engine src/main.cpp)  # 生成时启用和add_library不兼容
target_include_directories(engine 
PUBLIC 
	include
	include/core
    eigen
    tomlplusplus
)

# PRIVATE 头文件搜索路径不会顺延  
# PUBLIC则会扩展顺延  即 B依赖hpp   A依赖B 则 A也可寻得hpp
# INTERFACE 单纯依赖 用于不编译的头文件  纯头文件库可使用
# target一类命令中 前者依赖后者 
target_compile_features(engine PUBLIC cxx_std_17)	#指定语言版本

target_link_libraries(engine 
PUBLIC 
	glfw  
	toml++ 
	)
		 
target_precompile_headers(engine PUBLIC include/pch.hpp)
 