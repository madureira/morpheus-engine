#include "Engine.h"
#include "Window/Window.h"
#include "Core/Event/EventBus.h"
#include "Core/App/App.h"

namespace Morpheus {

	Engine::Engine()
		: m_Window(new Window("Morpheus", 1280, 768, true)),
		m_EventBus(new EventBus()),
		m_App(nullptr)
	{
	}

	void Engine::Initialize(App* app)
	{
		this->m_App = app;
		this->m_App->Initialize(this->m_EventBus);
	}

	void Engine::Run()
	{
		while (this->m_Window->IsOpen())
		{
			this->m_Window->PollEvents();
			this->m_App->OnFrameStarted();
			this->m_Window->SwapBuffers();
		}
	}

	Engine::~Engine()
	{
		delete this->m_Window;
		delete this->m_EventBus;
		delete this->m_App;
	}

}