#include "GameApp.h"

namespace Game {

	GameApp::GameApp()
		: m_InitialWindowWidth(800)
		, m_InitialWindowHeight(600)
		, m_SpriteRenderer(nullptr)
		, m_Texture(nullptr)
		, m_Normal(nullptr)
		, m_Specular(nullptr)
		, m_TexturePlayer(nullptr)
		, m_NormalPlayer(nullptr)
		, m_SpecularPlayer(nullptr)
	{
	}

	GameApp::~GameApp()
	{
		delete this->m_SpriteRenderer;
		delete this->m_Texture;
		delete this->m_Normal;
		delete this->m_Specular;
		delete this->m_TexturePlayer;
		delete this->m_NormalPlayer;
		delete this->m_SpecularPlayer;
	}

	void GameApp::Initialize(entt::registry& registry)
	{
		auto& settingsEntity = registry.ctx<Morpheus::SettingsEntity>();
		auto& settingsSize = registry.get<Morpheus::SettingsComponent>(settingsEntity.id);

		this->m_InitialWindowWidth = settingsSize.windowWidth;
		this->m_InitialWindowHeight = settingsSize.windowHeight;

		this->m_SpriteRenderer = new Morpheus::SpriteRenderer(registry, glm::vec2(this->m_InitialWindowWidth, this->m_InitialWindowHeight));

		this->m_Texture = new Morpheus::Texture("Assets/images/tileset.png");
		this->m_Normal = new Morpheus::Texture("Assets/images/tileset_n.png");
		this->m_Specular = new Morpheus::Texture("Assets/images/tileset_s.png");

		this->m_TexturePlayer = new Morpheus::Texture("Assets/images/ash.png");
		this->m_NormalPlayer = new Morpheus::Texture("Assets/images/ash_n.png");
		this->m_SpecularPlayer = new Morpheus::Texture("Assets/images/ash_s.png");

		this->m_Tiles = Morpheus::MapLoader::load("Assets/maps/level_1/map_3.json");
	}

	void GameApp::OnFrameStarted(entt::registry& registry, double deltaTime, int currentFrame, int frameRate)
	{
		static const int tileSize = 40;
		static const int columns = (1920 / tileSize) - 1;
		static const int rows = (1080 / tileSize) - 2;
		static const int layers = 3;
		static const int distance = -10;
		static const int margin = tileSize;
		static const int speed = 5;
		static int playerX = 0;
		static int playerY = 0;
		static float zoom = 1.0f;
		static const float scaleFactor = 0.025f;
		static glm::vec4 ambienteColor(1.0f, 1.0f, 1.f, 0.25f);

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

		for (const auto& tile : this->m_Tiles)
		{
			this->m_SpriteRenderer->Draw(this->m_Texture, this->m_Normal, this->m_Specular, tile->destRect, tile->sourceRect, glm::vec4(1, 1, 1, 1));
		}

		this->m_SpriteRenderer->SetScale(zoom);

		//this->m_SpriteRenderer->SetAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.01f));

		this->m_SpriteRenderer->SetAmbientColor(ambienteColor);
		this->m_SpriteRenderer->EnableNormal(!inputState.SPACE);
		this->m_SpriteRenderer->EnableSpecular(!inputState.LEFT_CONTROL);
		this->m_SpriteRenderer->EnableWireframe(inputState.LEFT_SHIFT);

		//this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));
		this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.01f, 1.0f, 20.0f));

		this->m_SpriteRenderer->Render();

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

		glm::vec4 destPlayerPos(750.0, 400.0 - zoom, 64, 64);

		this->m_SpriteRenderer->Draw(
			this->m_TexturePlayer,
			this->m_NormalPlayer,
			this->m_SpecularPlayer,
			destPlayerPos,
			spriteFrame,
			glm::vec4(1, 1, 1, 1)
		);

		//this->m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.1f, 1.0f, 900.0f));
		this->m_SpriteRenderer->AddSpotLight(glm::vec3(560.0, 300.0 - zoom, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.01f, 1.0f, 20.0f));

		this->m_SpriteRenderer->Render();
	}

	void GameApp::FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate)
	{
	}

}
