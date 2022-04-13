#define STB_IMAGE_IMPLEMENTATION

#include "Application.h"
#include "IconsFontAwesome5.h"
#include "UI.h"
#include "stb_image.h"
#include <stdio.h>
#include <string>

namespace MikuMikuWorld
{
	void frameBufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		if (width && height)
		{
			Application::screenWidth = width;
			Application::screenHeight = height;
		}

		glViewport(0, 0, width, height);
	}

	void loadIcon(std::string filepath, GLFWwindow* window)
	{
		GLFWimage images[1];
		images[0].pixels = stbi_load(filepath.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(window, 1, images);
		stbi_image_free(images[0].pixels);
	}

	bool Application::initOpenGL()
	{
		// GLFW initializion
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		window = glfwCreateWindow(1280, 720, windowTitleNew, NULL, NULL);
		if (window == NULL)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		// GLAD initializtion
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return false;
		}

		glViewport(0, 0, 1280, 720);
		glfwSwapInterval(1);
		glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

		loadIcon(appDir + "res/mmw_icon.png", window);

		glLineWidth(1.0f);
		glPointSize(1.0f);
		glEnable(GL_MULTISAMPLE);
		glEnablei(GL_BLEND, 0);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

		return true;
	}

	bool Application::initImgui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO* io = &ImGui::GetIO();

		io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io->ConfigWindowsMoveFromTitleBarOnly = true;
		io->ConfigViewportsNoDefaultParent = true;
		io->KeyRepeatRate = 0.15f;
		io->IniFilename = NULL;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		
		ImFontConfig fontConfig;
		fontConfig.MergeMode = true;
		fontConfig.GlyphMinAdvanceX = 13.0f;
		static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

		//io->Fonts->AddFontFromFileTTF(std::string("res/fonts/NotoSansJP-VF.ttf").c_str(), 16, NULL, io->Fonts->GetGlyphRangesDefault());
		io->Fonts->AddFontFromFileTTF(std::string("res/fonts/NotoSansJP-Regular.otf").c_str(), 18, NULL, io->Fonts->GetGlyphRangesJapanese());
		io->Fonts->AddFontFromFileTTF(std::string("res/fonts/fa-solid-900.ttf").c_str(), 14.0f, &fontConfig, iconRanges);
		
		return true;
	}

	void Application::setImguiStyle()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		style->FramePadding.x = 2;
		style->FramePadding.y = 2;
		style->ItemSpacing.x = 3;
		style->ItemSpacing.y = 4;
		style->WindowPadding.x = 8;
		style->WindowRounding = 4;
		style->WindowBorderSize = 1;
		style->FrameBorderSize = 0;
		style->FrameRounding = 1;
		style->ScrollbarRounding = 4;
		style->ChildRounding = 2;
		style->PopupRounding = 4;
		style->GrabRounding = 1.0f;
		style->TabRounding = 2;
		style->ScrollbarSize = 16;

		style->AntiAliasedLines = true;
		style->AntiAliasedFill = true;

		ImVec4* colors = style->Colors;
		colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.10f, 0.10f, 0.10f, 0.85f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.10f, 0.10f, 0.10f, 0.35f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.44f, 0.75f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.16f, 0.44f, 0.75f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.48f, 0.88f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.44f, 0.75f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.19f, 0.48f, 0.88f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.16f, 0.44f, 0.75f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
	}
}