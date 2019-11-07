#pragma once

namespace Morpheus {

	class Window;
	class EventBus;
	class App;

	class Engine
	{
	private:
		Window* m_Window;
		EventBus* m_EventBus;
		App* m_App;

	public:
		Engine();
		~Engine();
		void Initialize(App* app);
		void Run();
	};

}