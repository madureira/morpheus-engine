#include "MorpheusEditor.h"

#include <imgui.h>
#include "Vendors/imgui_impl_glfw.h"
#include "Vendors/imgui_impl_opengl3.h"
#include "Vendors/IconsFontAwesome5.h"
#include "Theme.h"
#include "Engine/ECS/Components/WindowComponent.h"

namespace Editor {

	MorpheusEditor::MorpheusEditor()
		: m_Menubar(nullptr),
		m_Actionbar(nullptr),
		m_Dock(nullptr)
	{
	}

	MorpheusEditor::~MorpheusEditor()
	{
		delete this->m_Menubar;
		delete this->m_Actionbar;
		delete this->m_Dock;
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void MorpheusEditor::Initialize(entt::registry& registry)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.IniFilename = NULL;                                      // Disable imgui.ini
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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

		auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
		auto& windowComponent = registry.get<Morpheus::WindowComponent>(windowEntity.id);
		registry.assign<Morpheus::ColorComponent>(windowEntity.id, 0.0f, 0.0f, 0.0f, 1.0f);

		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(windowComponent.GetNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 430");

		this->m_Menubar = new Menubar();
		this->m_Actionbar = new Actionbar();
		this->m_Dock = new Dock(registry);
	}

	void MorpheusEditor::OnFrameStarted(entt::registry& registry, double deltaTime, int currentFrame, int frameRate)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
		auto& windowSize = registry.get<Morpheus::SizeComponent>(windowEntity.id);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)windowSize.width, (float)windowSize.height);

		this->m_Menubar->Draw(registry);
		this->m_Actionbar->UpdateFrameRate(frameRate);
		this->m_Actionbar->Draw(registry);
		this->m_Dock->Draw(registry);

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void MorpheusEditor::FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate)
	{
	}
}
