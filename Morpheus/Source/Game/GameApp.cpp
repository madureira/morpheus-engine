#include "GameApp.h"

namespace Game {

	GameApp::~GameApp()
	{
		delete this->m_SpriteRenderer;
		delete this->m_Texture;
	}

	void GameApp::Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus)
	{
		this->m_Settings = pSettings;
		this->m_EventBus = pEventBus;
		this->m_EventBus->subscribe(this, &GameApp::InputHandler);

		this->m_SpriteRenderer = new Morpheus::SpriteRenderer(glm::vec2(this->m_Settings->GetWindowWidth(), this->m_Settings->GetWindowHeight()));
		this->m_Texture = new Morpheus::Texture("Assets/images/tileset.png");
		this->m_Normal = new Morpheus::Texture("Assets/images/tileset_n.png");
	}

	void GameApp::OnFrameStarted(double deltaTime, int frame)
	{
		static const int tileSize = 40;
		static const int columns = (this->m_Settings->GetWindowWidth() / tileSize) - 1;
		static const int rows = (this->m_Settings->GetWindowHeight() / tileSize) - 2;
		static const int layers = 5;
		static const int distance = -10;
		static const int margin = tileSize;
		static const int speed = 5;
		static int playerX = 0;
		static int playerY = 0;
		static float zoom = 1.0f;
		static const float scaleFactor = 0.025f;

		if (this->m_InputState.UP)
		{
			playerY += speed;
		}

		if (this->m_InputState.DOWN)
		{
			playerY -= speed;
		}

		if (this->m_InputState.RIGHT)
		{
			playerX += speed;
		}

		if (this->m_InputState.LEFT)
		{
			playerX -= speed;
		}

		if (this->m_InputState.W)
		{

			zoom += scaleFactor;
		}

		if (this->m_InputState.S)
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

						glm::vec4(margin + x * tileSize + z * distance + playerX, margin + y * tileSize + z * distance + playerY, tileSize, tileSize),

						getTile(tileSize, z)

						,glm::vec4(x / 10.f, y / 10.f, z / 10.f, 1.0f)
					);
				}
			}
		}

		this->m_SpriteRenderer->SetScale(zoom);

		this->m_SpriteRenderer->SetAmbientColor(glm::vec4(1.0f, 1.0f, 1.f, 0.2f));

		this->m_SpriteRenderer->AddLightSource(glm::vec3(300.0, 200.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));

		this->m_SpriteRenderer->AddLightSource(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));

		this->m_SpriteRenderer->AddLightSource(glm::vec3(300.0 + playerX, 200.0 + (-playerY), 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));

		this->m_SpriteRenderer->AddLightSource(glm::vec3(600.0 + playerX, 400.0 + (-playerY), 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));

		this->m_SpriteRenderer->Render();
	}

	void GameApp::FrameListener(double deltaTime, int frame)
	{
	}

	void GameApp::InputHandler(Morpheus::InputEvent* pEvent)
	{
		this->m_InputState = pEvent->GetState();
	}

	glm::vec4 GameApp::getTile(int tileSize, int layer)
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
