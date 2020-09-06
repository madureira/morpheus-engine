#include "MorpheusEditor.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <Engine/Util/NumberUtil.h>
#include <Engine/Util/HardwareUtil.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Containers/Dock/Dock.h"
#include "Editor/Containers/Footer/Footer.h"
#include "Editor/Containers/Menubar/Menubar.h"
#include "Editor/Containers/Actionbar/Actionbar.h"
#include "Vendors/ImGuiImpl/imgui_impl_opengl3.h"
#include "Vendors/ImGuiImpl/imgui_impl_glfw.h"
#include "Vendors/IconsFontAwesome5/IconsFontAwesome5.h"
#include "Theme.h"

namespace Editor {

    MorpheusEditor::MorpheusEditor()
        : m_Menubar(nullptr)
        , m_Actionbar(nullptr)
        , m_Dock(nullptr)
        , m_Footer(nullptr)
    {
    }

    MorpheusEditor::~MorpheusEditor()
    {
        delete this->m_Menubar;
        delete this->m_Actionbar;
        delete this->m_Dock;
        delete this->m_Footer;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void MorpheusEditor::Initialize(entt::registry& registry)
    {
        ME_LOG_INFO("CPU info: {0}", Morpheus::HardwareUtil::GetCPUInfo());
        ME_LOG_INFO("CPU available cores: {0}", Morpheus::HardwareUtil::GetCPUNumberOfCores());
        ME_LOG_INFO("RAM: {0}GB", Morpheus::HardwareUtil::BytesToGiga(Morpheus::HardwareUtil::GetTotalRAM()));
        ME_LOG_INFO("GPU: {0} - {1}", Morpheus::HardwareUtil::GetGPUModel(), Morpheus::HardwareUtil::GetGPUVendor());
        ME_LOG_INFO("OpenGL: {0}", Morpheus::HardwareUtil::GetRendererAPI());

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiDockNodeFlags_PassthruCentralNode;
        io.IniFilename = NULL; // Disable imgui.ini

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

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
        registry.assign<Morpheus::ColorComponent>(windowEntity.id, 0.0f, 0.0f, 0.0f, 0.5f);

        Morpheus::ProjectEntity projectEntity{ registry.create() };
        projectEntity.path = "";
        registry.set<Morpheus::ProjectEntity>(projectEntity);

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(windowComponent.GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 430");

        this->m_Menubar = new Menubar();
        this->m_Actionbar = new Actionbar();
        this->m_Dock = new Dock(registry);
        this->m_Footer = new Footer();
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

        this->m_Menubar->Render(registry);
        this->m_Actionbar->Render(registry);
        this->m_Dock->Render(registry);
        this->m_Footer->Render(registry);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* pBackupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(pBackupCurrentContext);
        }
    }

    void MorpheusEditor::FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate)
    {
    }
}
