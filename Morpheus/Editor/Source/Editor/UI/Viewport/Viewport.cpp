#include "Viewport.h"
#include <glad/glad.h>

namespace Editor {

	Viewport::Viewport(entt::registry& registry)
	{
		auto& settingsEntity = registry.ctx<Morpheus::SettingsEntity>();
		auto& settingsSize = registry.get<Morpheus::SettingsComponent>(settingsEntity.id);
		this->m_InitialWindowWidth = settingsSize.windowWidth;
		this->m_InitialWindowHeight = settingsSize.windowHeight;

		// Create Frame Buffer
		glGenFramebuffers(1, &this->m_FBO);

		// Generate render texture
		glGenTextures(1, &this->m_TextureColorBuffer);

		// Bind the texture used to paint the GL data on the IMGUI window
		glBindTexture(GL_TEXTURE_2D, this->m_TextureColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_InitialWindowWidth, this->m_InitialWindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_TextureColorBuffer, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		this->m_Shader = new Morpheus::Shader("Assets/shaders/viewport.vert", "Assets/shaders/viewport.frag");

		this->m_Vertices[0] = -1.0f;
		this->m_Vertices[1] = -1.0f;
		this->m_Vertices[2] = 0.0f;
		this->m_Vertices[3] = 1.0f;
		this->m_Vertices[4] = -1.0f;
		this->m_Vertices[5] = 0.0f;
		this->m_Vertices[6] = 0.0f;
		this->m_Vertices[7] = 1.0f;
		this->m_Vertices[8] = 0.0f;

		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_Vertices), this->m_Vertices, GL_STATIC_DRAW);
	}

	Viewport::~Viewport()
	{
		delete this->m_Shader;
	}

	void Viewport::ChangeColor(glm::vec4& color)
	{
		this->m_Color = color;
	}

	void Viewport::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_VIDEO" Scene###scene");
		{
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 size = ImGui::GetWindowSize();

			this->m_FrameBufferRect = glm::vec4(pos.x, pos.y, size.x, size.y);

			glViewport(0, 0, this->m_InitialWindowWidth, this->m_InitialWindowHeight);
			glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);

			auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
			auto& bgColor = registry.get<Morpheus::ColorComponent>(windowEntity.id);

			glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// TODO: Call the game rendering here
			this->m_Shader->Enable();
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);
			this->m_Shader->Disable();


			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, this->m_InitialWindowWidth, this->m_InitialWindowHeight);

			// Get FBO texture dimensions
			float texPosX = this->m_FrameBufferRect.x;
			float texPosY = this->m_FrameBufferRect.y;
			float texSizeW = this->m_FrameBufferRect.z;
			float texSizeH = this->m_FrameBufferRect.w;
			int marginLeft = 8;
			int marginBottom = 32;

			// Add the texture to it's draw list and render at the when ImGui::Render() is called.
			ImGui::GetWindowDrawList()->AddImage(
				(void*)this->m_FBO,
				ImVec2(texPosX, texPosY),
				ImVec2(texPosX + texSizeW - marginLeft, texPosY + texSizeH - marginBottom),
				ImVec2(0, 1),
				ImVec2(1, 0)
			);
		}
		ImGui::End();
	}

}
