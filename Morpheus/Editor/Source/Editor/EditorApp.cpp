#include "EditorApp.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "Vendors/imgui_impl_glfw.h"
#include "Vendors/imgui_impl_opengl3.h"
#include "Vendors/IconsFontAwesome5.h"
#include "Theme.h"

namespace Editor {

	EditorApp::~EditorApp()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void EditorApp::Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus, Morpheus::Window* pWindow)
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
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		io.IniFilename = NULL;

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

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(this->m_Window->GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}

	void EditorApp::OnFrameStarted(double deltaTime, int frame)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)this->m_Window->GetWidth(), (float)this->m_Window->GetHeight());


		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem(ICON_FA_FOLDER_PLUS "   New Project...")) {}
				if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "  Open...")) {}
				if (ImGui::MenuItem(ICON_FA_SAVE"   Save")) { }
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FA_POWER_OFF"   Exit")) {
					this->m_Window->Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		bool showActionBar = true;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoDocking;

		ImGui::SetNextWindowPos(ImVec2(0.0f, 22.0f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 32.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::Begin("Actions", &showActionBar, windowFlags);
		{
			ImGui::Button(ICON_FA_ARROWS_ALT);
			ImGui::SameLine();
			ImGui::Button(ICON_FA_SYNC_ALT);
			ImGui::SameLine();
			ImGui::Button(ICON_FA_EXPAND_ARROWS_ALT);
			ImGui::SameLine();
			ImGui::Button(ICON_FA_PLAY);
			ImGui::SameLine();
			ImGui::Button(ICON_FA_PAUSE);
		}
		ImGui::End();
		ImGui::PopStyleVar();



		bool dockEnabled = true;
		ImGuiWindowFlags dockFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		ImGuiID dockspaceID = ImGui::GetID("MainDock");

		ImGui::SetNextWindowPos(ImVec2(0.0f, 54.0f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y - 54.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		if (ImGui::Begin("Engine", &dockEnabled, dockFlags))
		{
			if (!ImGui::DockBuilderGetNode(dockspaceID)) {
				ImGui::DockBuilderRemoveNode(dockspaceID);
				ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

				ImGuiID dock_main_id = dockspaceID;
				ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id, ImGuiDir_Right, 0.2f, nullptr, &dock_down_id);

				ImGui::DockBuilderDockWindow("Inspector", dock_right_id);
				ImGui::DockBuilderDockWindow("Hierarchy", dock_left_id);
				ImGui::DockBuilderDockWindow("Project", dock_down_id);
				ImGui::DockBuilderDockWindow("Console", dock_down_right_id);
				ImGui::DockBuilderDockWindow("Scene", dock_main_id);

				ImGui::DockBuilderFinish(dock_main_id);
			}

			ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton;
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);


			ImGui::Begin("Inspector");
			ImGui::End();

			ImGui::Begin("Hierarchy");
			ImGui::End();

			ImGui::Begin("Project");
			ImGui::End();

			ImGui::Begin("Console");
			ImGui::End();

			ImGui::Begin("Scene");
			ImGui::End();


			ImGui::End();
		}
		ImGui::PopStyleVar();



		//ImGui::ShowDemoWindow();

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

	void EditorApp::FrameListener(double deltaTime, int frame)
	{
	}
}
