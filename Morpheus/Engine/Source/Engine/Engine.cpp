#include "mepch.h"
#include "Engine.h"
#include "Engine/App.h"
#include "Engine/Config/Settings.h"
#include "Engine/Window/Window.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/Mouse.h"
#include "Engine/Debug/Performance.h"
#include "Engine/ECS/Components/WindowComponent.h"

namespace Morpheus {

    Engine::Engine()
        : m_App(nullptr)
    {
        Morpheus::Log::Init();

        m_Settings = new Settings(m_Registry);

        // The SettingsEntity needs to be registered before everything
        Morpheus::SettingsEntity settingsEntity{ m_Registry.create() };
        m_Registry.set<Morpheus::SettingsEntity>(settingsEntity);
        m_Registry.emplace<Morpheus::SettingsComponent>(settingsEntity.id, m_Settings->GetSettings());

        m_Window = new Window(m_Registry);

        RegisterECS();

        m_Performance = new Performance(m_Settings);
        m_Mouse = new Mouse(m_Registry, m_Window->GetNativeWindow());
        m_Input = new Input(m_Registry, m_Window->GetNativeWindow());
    }

    Engine::~Engine()
    {
        delete m_Performance;
        delete m_Input;
        delete m_Mouse;
        delete m_Window;
        delete m_Settings;
    }

    void Engine::RegisterECS()
    {
        Morpheus::WindowEntity windowEntity{ m_Registry.create() };
        m_Registry.set<Morpheus::WindowEntity>(windowEntity);
        m_Registry.emplace<Morpheus::WindowComponent>(windowEntity.id, m_Window);
        m_Registry.emplace<Morpheus::SizeComponent>(windowEntity.id, m_Settings->GetWindowWidth(), m_Settings->GetWindowHeight());
        m_Registry.emplace<Morpheus::DropFilesComponent>(windowEntity.id, std::vector<std::string>());

        Morpheus::MouseEntity mouseEntity{ m_Registry.create() };
        m_Registry.set<Morpheus::MouseEntity>(mouseEntity);
        m_Registry.emplace<Morpheus::MouseStateComponent>(mouseEntity.id);

        Morpheus::InputEntity inputEntity{ m_Registry.create() };
        m_Registry.set<Morpheus::InputEntity>(inputEntity);
        m_Registry.emplace<Morpheus::InputStateComponent>(inputEntity.id);

        Morpheus::StatisticsEntity statisticsEntity{ m_Registry.create() };
        m_Registry.set<Morpheus::StatisticsEntity>(statisticsEntity);
        m_Registry.emplace<Morpheus::StatisticsComponent>(statisticsEntity.id);
    }

    void Engine::Initialize(App* pApp)
    {
        m_App = pApp;
        m_App->Initialize(m_Registry);
    }

    void Engine::Start()
    {
        const int MAX_FPS = m_Settings->GetMaxFPS();
        const double MS_PER_FRAME = 1.0 / (MAX_FPS * 1.0);
        const double ONE_SECOND = 1.0;
        double lastFrameTime = 0.0;
        double lastTime = 0.0;
        int currentFrame = 0;
        int frameRate = 0;

        auto& statisticsEntity = m_Registry.ctx<Morpheus::StatisticsEntity>();
        auto& statistics = m_Registry.get<Morpheus::StatisticsComponent>(statisticsEntity.id);

        while (m_Window->IsOpen())
        {
            double currentTime = m_Window->GetTime();
            double deltaTime = currentTime - lastTime;

            m_Window->PollEvents();
            m_Mouse->Update(m_Registry);
            m_Input->Update(m_Registry);
            m_App->FrameListener(m_Registry, deltaTime, currentFrame, frameRate);

            if (m_Settings->IsVSyncOn() || deltaTime >= MS_PER_FRAME)
            {
                currentFrame++;

                double deltaFrame = currentTime - lastFrameTime;

                statistics.frameRate = frameRate;

                m_Window->Clear();
                m_App->OnFrameStarted(m_Registry, deltaFrame, currentFrame, frameRate);
                m_Performance->Show(frameRate, deltaTime);

                if (deltaFrame >= ONE_SECOND)
                {
                    frameRate = currentFrame;
                    lastFrameTime = currentTime;
                    currentFrame = 0;
                    statistics.frameDeltaTime = deltaTime;
                }

                lastTime = currentTime;
                m_Window->SwapBuffers();
            }

            statistics.vertices = 0;
            statistics.drawCalls = 0;
        }
    }

}
