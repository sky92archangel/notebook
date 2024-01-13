

#向工程添加多个头文件搜索路径  PROJECT_SOURCE_DIR 项目根目录路径  
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/glad/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/glfw/glfw-3.3.8.bin.WIN64/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/imgui/1.88)
#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/glew/glew-2.1.0/include)
#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/glm) 


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/glfw/glfw-3.3.8.bin.WIN64/lib-vc2022)
# LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/_dependency_/glew/glew-2.1.0/lib/Release/x64)

# file(GLOB GLFW_LIB_FILE ${PROJECT_SOURCE_DIR}/_dependency_/glfw/glfw-3.3.8.bin.WIN64/lib-vc2022)
# file(GLOB GLFW_LIB_FILE ${PROJECT_SOURCE_DIR}/_dependency_/glfw/glfw-3.3.8.bin.WIN64/lib-vc2022)

#将当前目录下的所有文件都放入变量DIR_SRCS内 

#file(GLOB DIR_SRC_IMGUI ${PROJECT_SOURCE_DIR}/_dependency_/imgui/1.88/*.cpp)  
file(GLOB DIR_SRC_IMGUI ${CMAKE_CURRENT_LIST_DIR}/src/imgui/*.cpp)  #这是被拷贝过来的cpp  也可以直接采用库的路径
file(GLOB DIR_SRC_CPP ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB DIR_SRC_C ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
# 与上述一样
#AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_LIST_DIR}/src/imgui/*.cpp DIR_SRC_IMGUI) 
#AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_LIST_DIR}/src/*.cpp DIR_SRC_CPP) 
#AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_LIST_DIR}/src/*.c DIR_SRC_C) 


###################################################
project(ImGuiDemoGlad)
#添加可执行程序
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRC_C} ${DIR_SRC_CPP} ${DIR_SRC_IMGUI}  )  

#将库链接过来
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
PRIVATE
    glfw3.lib
    opengl32.lib  
)
  

###################################################
#生成后拷贝动作
set(COPY_RES_FONT ${CMAKE_CURRENT_LIST_DIR}/Fonts)
#完成或者开始编译一个目标前，执行某些命令（例如拷贝，自动生成.in文件等）
add_custom_command(
		#指定名为${PROJECT_NAME}的目标，在它编译完成之后执行命令
        TARGET ${PROJECT_NAME}  POST_BUILD 
        #要执行的命令名字为 ${CMAKE_COMMAND} -E代表的是环境无关的文件操作 copy_directory是拷贝文件夹
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        #指定从哪拷贝到哪。这里是把build/Release拷贝到当前目录
        ${COPY_RES_FONT} #源位置
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/Fonts #目标位置
        )

#下述代码也可用 # COPY的语法是： file(COPY <填写你要拷贝的文件> DESTINATION <填写你要的输出目录>)
# file(COPY ${COPY_RES_FONT} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})