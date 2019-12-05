#pragma once

#include <entt/entt.hpp>

namespace Morpheus {

	class Settings;
	class EventBus;
	class Window;
	class Input;
	class Performance;
	class App;

	class Engine
	{
	private:
		Settings* m_Settings;
		EventBus* m_EventBus;
		Window* m_Window;
		Input* m_Input;
		Performance* m_Performance;
		App* m_App;
		entt::registry m_Registry;

	public:
		Engine();
		~Engine();
		void Initialize(App* pApp);
		void Start();
	};

}
