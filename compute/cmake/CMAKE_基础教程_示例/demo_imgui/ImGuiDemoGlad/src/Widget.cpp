#include "Widget.h"
#include "PathHelper.h"

/// <summary>
/// ��������
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="title"></param>
/// <param name="monitor"></param>
/// <param name="window"></param>
/// <returns></returns>
GLFWwindow* Widget::CreateWindows(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* window)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* HWindow = glfwCreateWindow(width, height, title, monitor, window);

	if (HWindow == NULL)
	{
		printf("create window failed\n");
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(HWindow);
	return HWindow;
}


/// <summary>
/// �趨����
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Widget::WindowSetting(int width, int height)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//printf("int GLEW Failed"); 
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	return;
}



bool editor_Bool;
/// <summary>
/// �˵���demo
/// </summary>
void MenuBarTest() {

	//create menu bar   �˵���
	ImGui::BeginMainMenuBar();
	ImGui::Text("barName");
	if (ImGui::BeginMenu(u8"�ļ�")) {

		//editor_Bool =   true;
		//editor_Bool = ImGui::MenuItem("editor", NULL, editor_Bool, true);
		if (ImGui::MenuItem("editor", NULL, editor_Bool, true)) {
			printf("click editor button\n");
			editor_Bool = !editor_Bool;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}
/// <summary>
/// ���text����demo
/// </summary>
void WidgetTest() {
	//window
	ImGui::Begin("window");
	ImGui::Text("imgui window");
	ImGui::End();
}

/// <summary>
/// imgui��Ⱦ
/// </summary>
void WidgetRender() {

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/// <summary>
/// ����imgui
/// </summary>
void Widget::RunWidget()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//�趨���������Ͽ�ͣ���Ӵ���
	ImGui::DockSpaceOverViewport();

	//�ٷ�ʵ��
	ImGui::ShowDemoWindow();
	  
	//��bool���Ƶ�imgui�Ӵ�
	if (editor_Bool)
	{
		WidgetTest();
	}
	//���� imgui�˵����Ӵ�
	MenuBarTest();
	 
	//��ʼ������Ⱦ
	WidgetRender();

}

/// <summary>
/// ���ڹر�ʱ�Ĵ���
/// </summary>
void Widget::CloseWidget()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

/// <summary>
/// ��ʼ��imgui
/// </summary>
/// <param name="HWindows"></param>
void Widget::InitImGui(GLFWwindow* HWindows)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(NULL);

	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	//���
	ImGui::StyleColorsDark();
	io.ConfigViewportsNoAutoMerge=true;

	//io.Fonts->AddFontFromFileTTF("R:/Z_BACKUP_ORDER/_PROJECT_/CPP/ImGuiDemo/_dependency_/Fonts/simhei.ttf",15.0f,NULL,io.Fonts->GetGlyphRangesChineseFull());
	//�ҵ���ǰĿ¼����λ�����ļ�
	std::string fontPathStr = GetCWD() + "/Fonts/simhei.ttf";  
	const char* fontPath = fontPathStr.c_str(); 
	io.Fonts->AddFontFromFileTTF(fontPath,15.0f,NULL,io.Fonts->GetGlyphRangesChineseFull());
	//io.Fonts->AddFontFromMemoryCompressedTTF
	ImGui_ImplGlfw_InitForOpenGL(HWindows, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//docking setting
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;  
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

}
