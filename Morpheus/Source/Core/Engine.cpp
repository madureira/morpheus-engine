#include "Engine.h"
#include "Config/Settings.h"
#include "Core/Window/Window.h"
#include "Core/Event/EventBus.h"
#include "Core/Input/Input.h"
#include "Core/App.h"
#include <chrono>
#include <thread>

namespace Morpheus {

	Engine::Engine()
		: m_Settings(nullptr),
		m_EventBus(nullptr),
		m_Window(nullptr),
		m_Input(nullptr),
		m_App(nullptr)
	{
		this->m_Settings = new Settings();
		this->m_EventBus = new EventBus();
		this->m_Window = new Window(
			this->m_Settings->GetWindowTitle(),
			this->m_Settings->GetWindowWidth(),
			this->m_Settings->GetWindowHeight(),
			this->m_Settings->GetRenderVSync(),
			this->m_EventBus
		);
		this->m_Input = new Input(this->m_EventBus);
	}

	void Engine::Initialize(App* app)
	{
		this->m_App = app;
		this->m_App->Initialize(this->m_EventBus);
	}

	void Engine::Start()
	{
		int FPS = this->m_Settings->GetRenderFPS();
		float secondsPerFrame = (1.0 / FPS) * 1000;
		int frames = 0;
		auto start = std::chrono::steady_clock::now();

		while (this->m_Window->IsOpen())
		{
			++frames;
			auto now = std::chrono::steady_clock::now();
			auto diff = now - start;
			auto end = now + std::chrono::milliseconds((int)secondsPerFrame);
			if (diff >= std::chrono::seconds(1))
			{
				start = now;
				std::cout << "\rFPS: " << frames;
				frames = 0;
			}

			this->m_Window->PollEvents();
			this->m_App->OnFrameStarted();

			std::this_thread::sleep_until(end);

			this->m_Window->SwapBuffers();
		}
	}

	Engine::~Engine()
	{
		delete this->m_App;
		delete this->m_Input;
		delete this->m_Window;
		delete this->m_EventBus;
		delete this->m_Settings;
	}

}
