
#include <Windows.h>
#include <iostream>
#include <string>


//#include "imgui.h"
//#include "imgui_impl_opengl3.h"
//#include "imgui_impl_glfw.h"

#define SCR_WIDTH 1200 
#define SCR_HEIGHT 800 

//#define GLEW_STATIC
//#include  <GL/glew.h>
//#define GLFW_STATIC
//#include  <GLFW/glfw3.h>

#include "Widget.h" 

 

int main() {

	printf("start\n");  


	Widget windowFunc =  Widget::Widget();
	GLFWwindow* HWindow = windowFunc.CreateWindows(SCR_WIDTH, SCR_HEIGHT,"title",NULL, NULL); 
	/*glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	GLFWwindow* HWindow = glfwCreateWindow(800, 600, "title", NULL, NULL); 
	if (HWindow == NULL)
	{
		printf("create window failed\n");
		glfwTerminate();
		return -1;
	} 
	glfwMakeContextCurrent(HWindow);*/

	windowFunc.WindowSetting(SCR_WIDTH, SCR_HEIGHT);
	/*glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("glew failed\n");
		glfwTerminate();
		return -1;
	} 
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);*/

	windowFunc.InitImGui(HWindow);
	//ΩÁ√Ê—≠ª∑
	while (!glfwWindowShouldClose(HWindow))
	{
		glClearColor(0.f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		windowFunc.RunWidget();

		glfwSwapBuffers(HWindow);
		glfwPollEvents();
	}
	 
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	return 0;
}

