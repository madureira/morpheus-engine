#pragma once

#include "Engine/ECS/ECS.h"

namespace Morpheus {

	class Settings;
	class Window;
	class Input;
	class Performance;
	class App;

	class Engine
	{
	private:
		Settings* m_Settings;
		Window* m_Window;
		Input* m_Input;
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
