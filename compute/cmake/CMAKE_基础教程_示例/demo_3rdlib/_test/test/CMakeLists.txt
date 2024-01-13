  
add_executable(cgmath ./cgmath.cpp)
add_test(NAME cgmath_test COMMAND $<TARGET_FILE:cgmath>)

#先前在主CAMKE文件内add_library指定的库
target_link_libraries(cgmath  PRIVATE engine)