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
	/// //��������
	/// </summary>
	/// <param name="width">���ڿ��</param>
	/// <param name="height">���ڸ߶�</param>
	/// <param name="title">������</param>
	/// <param name="monitor">������</param>
	/// <param name="window"></param>
	/// <returns></returns>
	GLFWwindow* CreateWindows(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window);
	/// <summary>
	///���崰��
	/// </summary>
	/// <param name="width">���ڿ��</param>
	/// <param name="height">���ڸ߶�</param>
	void WindowSetting(int width, int height);

	/// <summary>
	/// ���д���
	/// </summary>
	void RunWidget();

	/// <summary>
	/// ���ڹر�ʱ�Ĵ���
	/// </summary>
	void CloseWidget();

	/// <summary>
	/// ��ʼ��imgui
	/// </summary>
	/// <param name="HWindows">��Ҫ��IMGUI�Ĵ���</param>
	void InitImGui(GLFWwindow* HWindows);

};