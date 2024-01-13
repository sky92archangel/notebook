add_executable( rapidjson_test ) 

aux_source_directory(./ DIR_SRCS) 
target_sources(rapidjson_test PUBLIC ${DIR_SRCS})  #然后对执行者添加源文件
 
# find_package(spdlog CONFIG REQUIRED)
# target_link_libraries(vckpg_test PRIVATE spdlog::spdlog)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_vendor_/)

