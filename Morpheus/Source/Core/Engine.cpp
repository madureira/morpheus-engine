#include "Engine.h"

#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Config/Settings.h"
#include "Core/Window/Window.h"
#include "Core/Event/EventBus.h"
#include "Core/Input/Input.h"
#include "Core/App.h"
#include "Core/Shader/Shader.h"
#include "Core/Text/TextRenderer.h"

namespace Morpheus {

	Engine::Engine()
		: m_Settings(nullptr),
		m_EventBus(nullptr),
		m_Window(nullptr),
		m_TextShader(nullptr),
		m_TextRenderer(nullptr),
		m_Input(nullptr),
		m_App(nullptr)
	{
		this->m_Settings = new Settings();
		this->m_EventBus = new EventBus();
		this->m_Window = new Window(
			this->m_Settings->GetWindowTitle(),
			this->m_Settings->GetWindowWidth(),
			this->m_Settings->GetWindowHeight(),
			this->m_Settings->GetRenderVSync(),
			this->m_EventBus
		);
		this->m_Input = new Input(this->m_EventBus);
		this->m_TextShader = new Shader("Assets/shaders/text.vert", "Assets/shaders/text.frag");
		this->m_TextRenderer = new TextRenderer("Assets/fonts/roboto-regular.ttf");

		this->m_InitialWindowWidth = static_cast<GLfloat>(this->m_Window->GetWidth());
		this->m_InitialWindowHeight = static_cast<GLfloat>(this->m_Window->GetHeight());

		glm::mat4 projection = glm::ortho(0.0f, this->m_InitialWindowWidth, 0.0f, this->m_InitialWindowHeight);
		this->m_TextShader->Enable();
		glUniformMatrix4fv(glGetUniformLocation(this->m_TextShader->GetProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	}

	void Engine::Initialize(App* app)
	{
		this->m_App = app;
		this->m_App->Initialize(this->m_EventBus);
	}

	void Engine::Start()
	{
		const int MAX_FPS = this->m_Settings->GetRenderFPS();
		const double MS_PER_FRAME = 1.0 / (MAX_FPS * 1.0);
		const double ONE_SECOND = 1.0;
		double lastFrameTime = 0.0;
		double lastTime = 0.0;
		int frames = 0;
		int fpsToDisplay = 0;

		while (this->m_Window->IsOpen())
		{
			double currentTime = this->m_Window->GetTime();
			double deltaTime = currentTime - lastTime;

			this->m_Window->PollEvents();
			this->m_App->FrameListener(deltaTime, frames);

			if (deltaTime >= MS_PER_FRAME)
			{
				frames++;

				double deltaFrame = currentTime - lastFrameTime;

				this->m_Window->Clear();

				this->m_App->OnFrameStarted(deltaFrame, frames);

				this->DisplayFPS(fpsToDisplay, deltaTime);

				if (deltaFrame >= ONE_SECOND)
				{
					fpsToDisplay = frames;
					lastFrameTime = currentTime;
					frames = 0;
				}

				lastTime = currentTime;
				this->m_Window->SwapBuffers();
			}
		}
	}

	void Engine::DisplayFPS(unsigned int frames, double deltaTime)
	{
		const std::string fps = "FPS: " + std::to_string(frames);
		const std::string timePerFrame = std::to_string(deltaTime) + " ms/frame";
		const float scale = 0.3f;
		const float originX = 5.0f;
		const float fpsTextPosY = this->m_InitialWindowHeight - 20.0f;
		const float timeTextPosY = this->m_InitialWindowHeight - 40.0f;

		this->m_TextRenderer->Render(*this->m_TextShader, fps, originX, fpsTextPosY, scale, glm::vec3(0.5f, 0.8f, 0.2f));
		this->m_TextRenderer->Render(*this->m_TextShader, timePerFrame, originX, timeTextPosY, scale, glm::vec3(0.3f, 0.7f, 0.9f));
	}

	Engine::~Engine()
	{
		delete this->m_App;
		delete this->m_Input;
		delete this->m_TextRenderer;
		delete this->m_TextShader;
		delete this->m_Window;
		delete this->m_EventBus;
		delete this->m_Settings;
	}

}
