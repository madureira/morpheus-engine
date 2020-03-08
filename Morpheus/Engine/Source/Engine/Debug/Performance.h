#pragma once

namespace Morpheus {

	class Settings;
	class Shader;
	class TextRenderer;

	class Performance final
	{
	private:
		Settings* m_Settings;
		Shader* m_TextShader;
		TextRenderer* m_TextRenderer;
		float m_InitialWindowWidth;
		float m_InitialWindowHeight;

	public:
		Performance(Settings* pSettings);
		~Performance();

		void Show(unsigned int frames, double deltaTime);
	};

}
