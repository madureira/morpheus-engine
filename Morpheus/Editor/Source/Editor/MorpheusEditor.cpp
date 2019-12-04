#include "MorpheusEditor.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include "Vendors/imgui_impl_glfw.h"
#include "Vendors/imgui_impl_opengl3.h"
#include "Vendors/IconsFontAwesome5.h"
#include "Theme.h"

namespace Editor {

	MorpheusEditor::~MorpheusEditor()
	{
		delete this->m_Menubar;
		delete this->m_Actionbar;
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void MorpheusEditor::Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus, Morpheus::Window* pWindow)
	{
		this->m_Settings = pSettings;
		this->m_EventBus = pEventBus;
		this->m_Window = pWindow;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.IniFilename = NULL;                                      // Disable imgui.ini

		// Loads editor fonts
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;

		ImFont* textFont = io.Fonts->AddFontFromFileTTF("Assets/fonts/roboto-regular.ttf", 16.0f);
		IM_ASSERT(textFont != NULL);

		ImFont* iconsFont = io.Fonts->AddFontFromFileTTF("Assets/fonts/fa-solid-900.ttf", 14.0f, &icons_config, icons_ranges);
		IM_ASSERT(iconsFont != NULL);

		// Setup Dear ImGui style
		ImGui_Theme::PhotoshopsUI();

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(this->m_Window->GetNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 430");

		this->m_Menubar = new Menubar(this->m_Window);
		this->m_Actionbar = new Actionbar();
		this->m_Dock = new Dock();
	}

	void MorpheusEditor::OnFrameStarted(double deltaTime, int frame)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)this->m_Window->GetWidth(), (float)this->m_Window->GetHeight());

		this->m_Menubar->Draw();
		this->m_Actionbar->Draw();
		this->m_Dock->Draw();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void MorpheusEditor::FrameListener(double deltaTime, int frame)
	{
	}
}
