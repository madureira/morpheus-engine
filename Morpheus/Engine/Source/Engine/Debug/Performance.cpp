#include "mepch.h"
#include "Performance.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/Shader/Shader.h"
#include "Engine/Config/Settings.h"
#include "Engine/Renderer/TextRenderer.h"

namespace Morpheus {

	Performance::Performance(Settings* pSettings)
		: m_Settings(pSettings)
		, m_TextShader(nullptr)
		, m_TextRenderer(nullptr)
		, m_InitialWindowWidth(0.0f)
		, m_InitialWindowHeight(0.0f)
	{
		if (this->m_Settings->IsDebug())
		{
			this->m_TextShader = new Shader("Assets/shaders/text.vert", "Assets/shaders/text.frag");
			this->m_TextRenderer = new TextRenderer("Assets/fonts/roboto-regular.ttf");

			this->m_InitialWindowWidth = static_cast<GLfloat>(this->m_Settings->GetWindowWidth());
			this->m_InitialWindowHeight = static_cast<GLfloat>(this->m_Settings->GetWindowHeight());

			glm::mat4 projection = glm::ortho(0.0f, this->m_InitialWindowWidth, 0.0f, this->m_InitialWindowHeight);
			this->m_TextShader->Enable();
			glUniformMatrix4fv(glGetUniformLocation(this->m_TextShader->GetProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		}
	}

	Performance::~Performance()
	{
		delete this->m_TextShader;
		delete this->m_TextRenderer;
	}

	void Performance::Show(unsigned int frames, double deltaTime)
	{
		if (this->m_Settings->IsDebug())
		{
			static const float scale = 0.3f;
			static const float originX = 5.0f;
			static const float rowHeight = 20.0f;
			const float fpsTextPosY = this->m_InitialWindowHeight - rowHeight;
			const float timeTextPosY = this->m_InitialWindowHeight - rowHeight * 2;
			const std::string fpsText = "FPS: " + std::to_string(frames);
			const std::string timeText = std::to_string(deltaTime) + " ms/frame";

			this->m_TextRenderer->Render(*this->m_TextShader, fpsText, originX, fpsTextPosY, scale, glm::vec3(0.5f, 0.8f, 0.2f));
			this->m_TextRenderer->Render(*this->m_TextShader, timeText, originX, timeTextPosY, scale, glm::vec3(0.3f, 0.7f, 0.9f));
		}
	}

}
