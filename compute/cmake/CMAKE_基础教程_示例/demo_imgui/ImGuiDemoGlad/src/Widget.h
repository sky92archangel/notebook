#pragma once


//
//#pragma comment(lib,"../_dependency_/glfw/glfw-3.3.8.bin.WIN32/lib-vc2022/glfw3.lib")
//#pragma comment(lib,"../_dependency_/glew/glew-2.1.0/lib/Release/Win32/glew32s.lib")


#include <iostream> 
 
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui_internal.h"

#define GLAD_STATIC
#include <glad/glad.h>
#define GLFW_STATIC
#include  <GLFW/glfw3.h> 

class Widget {

public:
	/// <summary>
	/// //创建窗口
	/// </summary>
	/// <param name="width">窗口宽度</param>
	/// <param name="height">窗口高度</param>
	/// <param name="title">窗口名</param>
	/// <param name="monitor">监视器</param>
	/// <param name="window"></param>
	/// <returns></returns>
	GLFWwindow* CreateWindows(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window);
	/// <summary>
	///定义窗口
	/// </summary>
	/// <param name="width">窗口宽度</param>
	/// <param name="height">窗口高度</param>
	void WindowSetting(int width, int height);

	/// <summary>
	/// 运行窗口
	/// </summary>
	void RunWidget();

	/// <summary>
	/// 窗口关闭时的处理
	/// </summary>
	void CloseWidget();

	/// <summary>
	/// 初始化imgui
	/// </summary>
	/// <param name="HWindows">需要放IMGUI的窗口</param>
	void InitImGui(GLFWwindow* HWindows);

};