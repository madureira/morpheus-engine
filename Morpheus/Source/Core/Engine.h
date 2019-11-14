#pragma once

namespace Morpheus {

	class App;
	class EventBus;
	class Input;
	class Window;
	class Settings;

	class Engine
	{
	private:
		App* m_App;
		EventBus* m_EventBus;
		Input* m_Input;
		Window* m_Window;
		Settings* m_Settings;

	public:
		Engine();
		~Engine();
		void Initialize(App* app);
		void Start();
	};

}
