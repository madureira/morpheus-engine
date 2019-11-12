#include "Engine.h"
#include "Window/Window.h"
#include "Core/Event/EventBus.h"
#include "Core/Input/Input.h"
#include "Core/App.h"

namespace Morpheus {

	Engine::Engine()
		: m_EventBus(new EventBus()),
		m_Window(nullptr),
		m_Input(nullptr),
		m_App(nullptr)
	{
		this->m_Window = new Window("Morpheus", 1280, 768, true, this->m_EventBus);
		this->m_Input = new Input(this->m_EventBus);
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
		delete this->m_App;
		delete this->m_EventBus;
	}

}