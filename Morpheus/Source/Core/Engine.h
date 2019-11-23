#pragma once

namespace Morpheus {

	class Settings;
	class EventBus;
	class Window;
	class Input;
	class Shader;
	class TextRenderer;
	class Performance;
	class App;

	class Engine
	{
	private:
		Settings* m_Settings;
		EventBus* m_EventBus;
		Window* m_Window;
		Input* m_Input;
		Shader* m_TextShader;
		TextRenderer* m_TextRenderer;
		Performance* m_Performance;
		App* m_App;

	public:
		Engine();
		~Engine();
		void Initialize(App* pApp);
		void Start();
	};

}
