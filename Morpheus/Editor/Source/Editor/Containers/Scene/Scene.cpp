#include "Scene.h"
#include <glad/glad.h>
#include <Engine/Log/Log.h>
#include <Engine/ECS/Components/WindowComponent.h>

namespace Editor {

	static int POS_X = 0;
	static int POS_Y = 0;
	static int OLD_POS_X = 0;
	static int OLD_POS_Y = 0;
	static bool IS_DRAGGING = false;

	Scene::Scene(entt::registry& registry)
		: m_TextureColorBuffer(0)
	{
		auto& settingsEntity = registry.ctx<Morpheus::SettingsEntity>();
		auto& settingsSize = registry.get<Morpheus::SettingsComponent>(settingsEntity.id);
		this->m_InitialWindowWidth = settingsSize.windowWidth;
		this->m_InitialWindowHeight = settingsSize.windowHeight;

		this->GenerateTextureBuffer();
		this->GenerateCheckerboardImage();
		this->InitializeApp(registry);
	}

	Scene::~Scene()
	{
		this->ShutdownApp();
	}

	void Scene::Render(entt::registry& registry)
	{
		static bool* show = NULL;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin(ICON_FA_CUBE"  Scene###scene", show, windowFlags);
		{
			this->ClearViewport(registry);
			this->UpdateApp(registry);
			this->RenderViewport(registry);
		}
		ImGui::End();
	}

	void Scene::InitializeApp(entt::registry& registry)
	{
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

		this->m_SpriteRenderer = new Morpheus::SpriteRenderer(registry, glm::vec2(this->m_InitialWindowWidth, this->m_InitialWindowHeight));

		this->m_Shader = new Morpheus::Shader("Assets/shaders/wireframe.vert", "Assets/shaders/wireframe.frag", "Assets/shaders/wireframe.geom");

		this->m_Texture = new Morpheus::Texture("Assets/images/tileset.png");
		this->m_Normal = new Morpheus::Texture("Assets/images/tileset_n.png");
		this->m_Specular = new Morpheus::Texture("Assets/images/tileset_s.png");

		this->m_TexturePlayer = new Morpheus::Texture("Assets/images/ash.png");
		this->m_NormalPlayer = new Morpheus::Texture("Assets/images/ash_n.png");
		this->m_SpecularPlayer = new Morpheus::Texture("Assets/images/ash_s.png");

		this->m_Tiles = Morpheus::MapLoader::load("Assets/maps/level_1/map_3.json");
	}

	void Scene::UpdateApp(entt::registry& registry)
	{
		auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

		if (projectEntity.scenes.empty())
		{
			return;
		}

		static const int tileSize = 40;
		static const int columns = (1280 / tileSize) - 1;
		static const int rows = (720 / tileSize) - 2;
		static const int layers = 3;
		static const int distance = -10;
		static const int margin = tileSize;
		static const int speed = 5;
		static int playerX = 0;
		static int playerY = 0;
		static float zoom = 1.0f;
		static const float scaleFactor = 0.25f;

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

		ImGuiIO& io = ImGui::GetIO();
		if (io.MouseWheel != 0.0f)
		{
			if (io.MouseWheel < 0)
			{
				zoom -= scaleFactor;
			}

			if (io.MouseWheel > 0)
			{
				zoom += scaleFactor;
			}
		}

		bool isMouseWheelPressed = io.MouseDown[2];

		if (isMouseWheelPressed)
		{
			glm::vec2 lookingAt = this->m_SpriteRenderer->LookingAt();

			if (!IS_DRAGGING)
			{
				IS_DRAGGING = true;
				OLD_POS_X = POS_X;
				OLD_POS_Y = POS_Y;
			}
			else
			{
				lookingAt.x += (OLD_POS_X - POS_X);
				lookingAt.y += (OLD_POS_Y - POS_Y);
				this->m_SpriteRenderer->LookAt(lookingAt.x, lookingAt.y);
			}
		}
		else
		{
			IS_DRAGGING = false;
			OLD_POS_X = 0;
			OLD_POS_Y = 0;
		}

		zoom = zoom < scaleFactor ? scaleFactor : zoom;
		glm::vec4 ambientColor(1.0f, 1.0f, 1.f, 0.25f);
		this->m_SpriteRenderer->SetScale(zoom);
		this->m_SpriteRenderer->SetAmbientColor(ambientColor);

		this->m_SpriteRenderer->EnableNormal(!inputState.SPACE);
		this->m_SpriteRenderer->EnableSpecular(!inputState.LEFT_CONTROL);
		this->m_SpriteRenderer->EnableWireframe(inputState.LEFT_SHIFT);


		glm::vec4 defaultColor(1, 1, 1, 1);
		// -------- TILES -------
		for (const auto& tile : this->m_Tiles)
		{
			this->m_SpriteRenderer->Draw(this->m_Texture, this->m_Normal, this->m_Specular, tile->destRect, tile->sourceRect, defaultColor);
		}
		this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.0001f, 0.2f, 900.0f)); // light floor player
		this->m_SpriteRenderer->AddSpotLight(glm::vec3(POS_X, POS_Y, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.0001f, 0.2f, 100.0f)); // light floor top-left
		// -------- END TILES -------


		// -------- PLAYER -------
		static int frameCount = 0;
		static int frame = 0;
		static int playerSpeed = 10;

		if (frameCount < playerSpeed)
		{
			frameCount++;
		}
		else
		{
			frameCount = 0;
			frame++;
		}

		if (frame == 4)
		{
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
			this->m_SpecularPlayer,
			glm::vec4(playerX, playerY, 64, 64),
			spriteFrame,
			defaultColor
		);

		this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.1f), glm::vec4(1.0f, 0.8f, 0.6f, 0.1f), glm::vec3(0.1f, 1.0f, 20.0f)); // light head player
		this->m_SpriteRenderer->AddSpotLight(glm::vec3(POS_X, POS_Y, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.0001f, 0.2f, 100.0f)); // light head top-left
		// -------- END PLAYER -------

		this->m_SpriteRenderer->Render();
	}

	void Scene::ShutdownApp()
	{
		delete this->m_SpriteRenderer;
		delete this->m_Shader;
		delete this->m_Texture;
		delete this->m_Normal;
		delete this->m_Specular;
		delete this->m_TexturePlayer;
		delete this->m_NormalPlayer;
		delete this->m_SpecularPlayer;
		for (auto pTile : this->m_Tiles)
		{
			delete pTile;
		}
		this->m_Tiles.clear();
	}

	void Scene::ClearViewport(entt::registry& registry)
	{
		auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
		auto& bgColor = registry.get<Morpheus::ColorComponent>(windowEntity.id);

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImGui::GetWindowSize();

		if ((size.x != this->m_InitialWindowWidth) || (size.y != this->m_InitialWindowHeight))
		{
			this->m_InitialWindowWidth = size.x;
			this->m_InitialWindowHeight = size.y;
			this->m_SpriteRenderer->SetScreenSize(glm::vec2(size.x, size.y));
			this->GenerateCheckerboardImage();
			this->GenerateTextureBuffer();
		}

		this->m_FrameBufferRect = glm::vec4(pos.x, pos.y, size.x, size.y);

		glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
		glViewport(0, 0, this->m_InitialWindowWidth, this->m_InitialWindowHeight);
		glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Scene::RenderViewport(entt::registry& registry)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Get FBO texture dimensions
		float texPosX = this->m_FrameBufferRect.x;
		float texPosY = this->m_FrameBufferRect.y;
		float texSizeW = this->m_FrameBufferRect.z;
		float texSizeH = this->m_FrameBufferRect.w;
		int marginLeft = 8;
		int marginBottom = 32;

		auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

		if (!projectEntity.scenes.empty())
		{
			ImGui::GetWindowDrawList()->AddImage(
				(void*)this->m_CheckerboardTextureID,
				ImVec2(texPosX, texPosY),
				ImVec2(texPosX + texSizeW - marginLeft, texPosY + texSizeH - marginBottom),
				ImVec2(0, 1),
				ImVec2(1, 0)
			);

			ImGui::GetWindowDrawList()->AddImage(
				(void*)this->m_FBO,
				ImVec2(texPosX, texPosY),
				ImVec2(texPosX + texSizeW - marginLeft, texPosY + texSizeH - marginBottom),
				ImVec2(0, 1),
				ImVec2(1, 0)
			);

			//if (ImGui::IsWindowHovered())
			//{
				auto& mouseEntity = registry.ctx<Morpheus::MouseEntity>();
				auto& mouseState = registry.get<Morpheus::MouseStateComponent>(mouseEntity.id);

				ImVec2 mousePos = ImGui::GetMousePos();
				POS_X = static_cast<int>(mousePos.x - texPosX);
				POS_Y = static_cast<int>(mousePos.y - texPosY);
				/*
				if (POS_X < 0) {
					POS_X = 0;
				}

				if (POS_Y < 0) {
					POS_Y = 0;
				}
				*/
			//}

			ImGui::Text(" x: %d", POS_X);
			ImGui::Text(" y: %d", POS_Y);
		}
	}

	void Scene::GenerateCheckerboardImage()
	{
		glDeleteTextures(1, &this->m_CheckerboardTextureID);

		int rows = this->m_InitialWindowWidth;
		int columns = this->m_InitialWindowHeight;
		int pixelRGBA = 4;

		GLubyte* image = new GLubyte[rows * columns * pixelRGBA];

		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				for (int k = 0; k < pixelRGBA; k++)
				{
					*(image + i * rows * pixelRGBA + j * pixelRGBA + k) = 0;
				}
			}
		}

		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				for (int k = 0; k < pixelRGBA; k++)
				{
					if (k < 3)
					{
						int color = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * CHECKERBOARD_INTENSITY;
						*(image + i * rows * pixelRGBA + j * pixelRGBA + k) = (GLubyte)color;
					}
					else
					{
						*(image + i * rows * pixelRGBA + j * pixelRGBA + k) = (GLubyte)CHECKERBOARD_INTENSITY;
					}
				}
			}
		}

		// Bind the texture used to paint the checkerboard pattern on the IMGUI background window
		glGenTextures(1, &this->m_CheckerboardTextureID);
		glBindTexture(GL_TEXTURE_2D, this->m_CheckerboardTextureID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rows, columns, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] image;
	}

	void Scene::GenerateTextureBuffer()
	{
		glDeleteTextures(1, &this->m_TextureColorBuffer);
		glDeleteFramebuffers(1, &this->m_FBO);

		// Generate render texture
		glGenTextures(1, &this->m_TextureColorBuffer);

		// Bind the texture used to paint the GL data on the IMGUI window
		glBindTexture(GL_TEXTURE_2D, this->m_TextureColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_InitialWindowWidth, this->m_InitialWindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Create Frame Buffer
		glGenFramebuffers(1, &this->m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_TextureColorBuffer, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
