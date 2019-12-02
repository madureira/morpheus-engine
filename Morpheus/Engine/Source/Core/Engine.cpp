#include "mepch.h"
#include "Engine.h"
#include "Core/Config/Settings.h"
#include "Core/Event/EventBus.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"
#include "Core/Debug/Performance.h"
#include "Core/App.h"

namespace Morpheus {

	Engine::Engine() : m_App(nullptr)
	{
		this->m_Settings = new Settings();
		this->m_EventBus = new EventBus();
		this->m_Window = new Window(this->m_Settings, this->m_EventBus);
		this->m_Input = new Input(this->m_EventBus, this->m_Window->GetNativeWindow());
		this->m_Performance = new Performance(this->m_Settings);
	}

	Engine::~Engine()
	{
		delete this->m_App;
		delete this->m_Performance;
		delete this->m_Input;
		delete this->m_Window;
		delete this->m_EventBus;
		delete this->m_Settings;
	}

	void Engine::Initialize(App* pApp)
	{
		this->m_App = pApp;
		this->m_App->Initialize(this->m_Settings, this->m_EventBus, this->m_Window);
	}

	void Engine::Start()
	{
		const int MAX_FPS = this->m_Settings->GetMaxFPS();
		const double MS_PER_FRAME = 1.0 / (MAX_FPS * 1.0);
		const double ONE_SECOND = 1.0;
		double lastFrameTime = 0.0;
		double lastTime = 0.0;
		int frames = 0;
		int fpsToDisplay = 0;

		while (this->m_Window->IsOpen())
		{
			double currentTime = this->m_Window->GetTime();
			double deltaTime = currentTime - lastTime;

			this->m_Window->PollEvents();
			this->m_Input->Update();
			this->m_App->FrameListener(deltaTime, frames);

			if (this->m_Settings->IsVSyncOn() || deltaTime >= MS_PER_FRAME)
			{
				frames++;

				double deltaFrame = currentTime - lastFrameTime;

				this->m_Window->Clear();
				this->m_App->OnFrameStarted(deltaFrame, frames);
				this->m_Performance->Show(fpsToDisplay, deltaTime);

				if (deltaFrame >= ONE_SECOND)
				{
					fpsToDisplay = frames;
					lastFrameTime = currentTime;
					frames = 0;
				}

				lastTime = currentTime;
				this->m_Window->SwapBuffers();
			}
		}
	}

}
