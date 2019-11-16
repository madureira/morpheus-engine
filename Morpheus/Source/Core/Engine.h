#pragma once

namespace Morpheus {

	class App;
	class EventBus;
	class Input;
	class Window;
	class Settings;
	class Shader;
	class TextRenderer;

	class Engine
	{
	private:
		App* m_App;
		EventBus* m_EventBus;
		Input* m_Input;
		Window* m_Window;
		Settings* m_Settings;
		Shader* m_TextShader;
		TextRenderer* m_TextRenderer;
		float m_InitialWindowWidth;
		float m_InitialWindowHeight;

	public:
		Engine();
		~Engine();
		void Initialize(App* app);
		void Start();
		void DisplayFPS(unsigned int frames, double deltaTime);
	};

}
