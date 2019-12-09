#include "mepch.h"
#include "Engine.h"
#include "Engine/Config/Settings.h"
#include "Engine/Window/Window.h"
#include "Engine/Input/Input.h"
#include "Engine/Debug/Performance.h"
#include "Engine/App.h"

namespace Morpheus {

	Engine::Engine() : m_App(nullptr)
	{
		this->m_Settings = new Settings();

		Morpheus::WindowEntity windowEntity{ this->m_Registry.create() };
		this->m_Registry.set<Morpheus::WindowEntity>(windowEntity);
		this->m_Registry.assign<Morpheus::SizeComponent>(windowEntity.id, this->m_Settings->GetWindowWidth(), this->m_Settings->GetWindowHeight());


		Morpheus::InputEntity inputEntity{ this->m_Registry.create() };
		this->m_Registry.set<Morpheus::InputEntity>(inputEntity);
		this->m_Registry.assign<Morpheus::InputStateComponent>(inputEntity.id);


		this->m_Window = new Window(this->m_Registry, this->m_Settings);
		this->m_Performance = new Performance(this->m_Settings);
		this->m_Input = new Input(this->m_Registry, this->m_Window->GetNativeWindow());
	}

	Engine::~Engine()
	{
		delete this->m_App;
		delete this->m_Performance;
		delete this->m_Input;
		delete this->m_Window;
		delete this->m_Settings;
	}

	void Engine::Initialize(App* pApp)
	{
		this->m_App = pApp;
		this->m_App->Initialize(this->m_Settings, this->m_Window, this->m_Registry);
	}

	void Engine::Start()
	{
		const int MAX_FPS = this->m_Settings->GetMaxFPS();
		const double MS_PER_FRAME = 1.0 / (MAX_FPS * 1.0);
		const double ONE_SECOND = 1.0;
		double lastFrameTime = 0.0;
		double lastTime = 0.0;
		int currentFrame = 0;
		int frameRate = 0;

		while (this->m_Window->IsOpen())
		{
			double currentTime = this->m_Window->GetTime();
			double deltaTime = currentTime - lastTime;

			this->m_Window->PollEvents();
			this->m_Input->Update(this->m_Registry);
			this->m_App->FrameListener(deltaTime, currentFrame, frameRate, this->m_Registry);

			if (this->m_Settings->IsVSyncOn() || deltaTime >= MS_PER_FRAME)
			{
				currentFrame++;

				double deltaFrame = currentTime - lastFrameTime;

				this->m_Window->Clear();
				this->m_App->OnFrameStarted(deltaFrame, currentFrame, frameRate, this->m_Registry);
				this->m_Performance->Show(frameRate, deltaTime);

				if (deltaFrame >= ONE_SECOND)
				{
					frameRate = currentFrame;
					lastFrameTime = currentTime;
					currentFrame = 0;
				}

				lastTime = currentTime;
				this->m_Window->SwapBuffers();
			}
		}
	}

}
