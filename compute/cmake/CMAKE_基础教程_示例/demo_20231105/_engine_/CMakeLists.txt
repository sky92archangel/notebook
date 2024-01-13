

add_executable( _engine_ )  # 生成时启用和add_library不兼容 先指定执行者
 
aux_source_directory(./src DIR_SRCS) 
aux_source_directory(./mylib DIR_SRCS) 
target_sources(_engine_ PUBLIC ${DIR_SRCS})  #然后对执行者添加源文件
 
#将vendor中打包的 Eigen库引入main程序scope
target_link_libraries(_engine_ PUBLIC EIGEN_LIBRARY_MODULE)
target_link_libraries(_engine_ PUBLIC EIGEN_TEST_LIB)
 
add_subdirectory(mylib)

