#pragma once

#include "Engine/ECS/ECS.h"

namespace Morpheus {

	class Settings;
	class Window;
	class Input;
	class Mouse;
	class Performance;
	class App;

	class Engine final
	{
	private:
		Settings* m_Settings;
		Window* m_Window;
		Input* m_Input;
		Mouse* m_Mouse;
		Performance* m_Performance;
		App* m_App;
		entt::registry m_Registry;

	public:
		Engine();
		~Engine();

		void RegisterECS();
		void Initialize(App* pApp);
		void Start();
	};

}
