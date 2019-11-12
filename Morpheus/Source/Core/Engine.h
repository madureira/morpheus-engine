#pragma once

namespace Morpheus {

	class App;
	class EventBus;
	class Input;
	class Window;

	class Engine
	{
	private:
		App* m_App;
		EventBus* m_EventBus;
		Input* m_Input;
		Window* m_Window;

	public:
		Engine();
		~Engine();
		void Initialize(App* app);
		void Run();
	};

}