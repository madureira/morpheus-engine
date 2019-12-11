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
		this->m_Vertices[2] =  0.0f;
		this->m_Vertices[3] =  1.0f;
		this->m_Vertices[4] = -1.0f;
		this->m_Vertices[5] =  0.0f;
		this->m_Vertices[6] =  0.0f;
		this->m_Vertices[7] =  1.0f;
		this->m_Vertices[8] =  0.0f;

		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_Vertices), this->m_Vertices, GL_STATIC_DRAW);



		this->m_SpriteRenderer = new Morpheus::SpriteRenderer(glm::vec2(this->m_InitialWindowWidth, this->m_InitialWindowHeight));

		this->m_Texture = new Morpheus::Texture("Assets/images/tileset.png");
		this->m_Normal = new Morpheus::Texture("Assets/images/tileset_n.png");

		this->m_TexturePlayer = new Morpheus::Texture("Assets/images/ash.png");
		this->m_NormalPlayer = new Morpheus::Texture("Assets/images/ash_n.png");
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
		auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
		auto& bgColor = registry.get<Morpheus::ColorComponent>(windowEntity.id);

		ImGui::Begin(ICON_FA_VIDEO" Scene###scene");
		{
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 size = ImGui::GetWindowSize();

			this->m_FrameBufferRect = glm::vec4(pos.x, pos.y, size.x, size.y);

			glViewport(0, 0, this->m_InitialWindowWidth, this->m_InitialWindowHeight);
			glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);



			glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			/*
			this->m_Shader->Enable();
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);
			this->m_Shader->Disable();
			*/





			
			static const int tileSize = 40;
			static const int columns = (1280 / tileSize) - 1;
			static const int rows = (720 / tileSize) - 2;
			static const int layers = 2;
			static const int distance = -10;
			static const int margin = tileSize;
			static const int speed = 1;
			static int playerX = 0;
			static int playerY = 0;
			static float zoom = 1.0f;
			static const float scaleFactor = 0.025f;

			auto& inputEntity = registry.ctx<Morpheus::InputEntity>();
			auto& inputState = registry.get<Morpheus::InputStateComponent>(inputEntity.id);

			if (inputState.UP)
			{
				playerY += speed;
			}

			if (inputState.DOWN)
			{
				playerY -= speed;
			}

			if (inputState.RIGHT)
			{
				playerX += speed;
			}

			if (inputState.LEFT)
			{
				playerX -= speed;
			}

			if (inputState.W)
			{
				zoom += scaleFactor;
			}

			if (inputState.S)
			{
				zoom -= scaleFactor;
			}

			zoom = zoom < scaleFactor ? scaleFactor : zoom;


			for (int z = 0; z < layers; z++)
			{
				for (int x = 0; x < columns; x++)
				{
					for (int y = 0; y < rows; y++)
					{
						this->m_SpriteRenderer->Draw(
							this->m_Texture,
							this->m_Normal,

							glm::vec4(margin + x * tileSize + z * distance - playerX, margin + y * tileSize + z * distance - playerY, tileSize, tileSize),

							getTile(tileSize, z)

							//,glm::vec4(x / 10.f, y / 10.f, z / 10.f, 1.0f)
						);
					}
				}
			}

			this->m_SpriteRenderer->SetScale(zoom);

			this->m_SpriteRenderer->SetAmbientColor(glm::vec4(1.0f, 1.0f, 1.f, 0.25f));

			this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));

			this->m_SpriteRenderer->Render();


			static int frameCount = 0;
			static int frame = 0;
			static int playerSpeed = 10;

			if (frameCount < playerSpeed)
			{
				frameCount++;
			}
			else {
				frameCount = 0;
				frame++;
			}

			if (frame == 4) {
				frame = 0;
			}

			int direction = frame;

			glm::vec4 spriteFrame;

			if (direction == 0)
			{
				spriteFrame = glm::vec4(0, 64, 64, 0);
			}

			if (direction == 1)
			{
				spriteFrame = glm::vec4(64, 64, 64 * 2, 0);
			}

			if (direction == 2)
			{
				spriteFrame = glm::vec4(64 * 2, 64, 64 * 3, 0);
			}

			if (direction == 3)
			{
				spriteFrame = glm::vec4(64 * 3, 64, 64 * 4, 0);
			}

			this->m_SpriteRenderer->Draw(
				this->m_TexturePlayer,
				this->m_NormalPlayer,

				//glm::vec4(playerX, playerY, 64, 64),
				glm::vec4(580, 300, 64, 64),

				spriteFrame
			);

			this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.1f, 1.0f, 900.0f));

			this->m_SpriteRenderer->Render();












			glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

	glm::vec4 Viewport::getTile(int tileSize, int layer)
	{
		if (layer == 0 || layer == 5 || layer == 10 || layer == 15)
		{
			return glm::vec4(tileSize, tileSize, tileSize * 2, 0);
		}

		if (layer == 1 || layer == 6 || layer == 11 || layer == 16)
		{
			return glm::vec4(0, tileSize, tileSize, 0);
		}

		if (layer == 2 || layer == 7 || layer == 12 || layer == 17)
		{
			return glm::vec4(tileSize * 4, tileSize, tileSize * 5, 0);
		}

		if (layer == 3 || layer == 8 || layer == 13 || layer == 18)
		{
			return glm::vec4(tileSize * 8, tileSize, tileSize * 9, 0);
		}

		if (layer == 4 || layer == 9 || layer == 14 || layer == 19)
		{
			return glm::vec4(tileSize * 4, tileSize * 4, tileSize * 5, tileSize * 3);
		}

		return glm::vec4(0, tileSize, tileSize, 0);
	}

}
