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
        delete m_SpriteRenderer;
        delete m_Texture;
        delete m_Normal;
        delete m_Specular;
        delete m_TexturePlayer;
        delete m_NormalPlayer;
        delete m_SpecularPlayer;
    }

    void GameApp::Initialize(entt::registry& registry)
    {
        auto& settingsEntity = registry.ctx<Morpheus::SettingsEntity>();
        auto& settingsSize = registry.get<Morpheus::SettingsComponent>(settingsEntity.id);

        m_InitialWindowWidth = settingsSize.windowWidth;
        m_InitialWindowHeight = settingsSize.windowHeight;

        m_SpriteRenderer = new Morpheus::SpriteRenderer(registry, glm::vec2(m_InitialWindowWidth, m_InitialWindowHeight));

        m_Texture = new Morpheus::Texture("Assets/images/tileset.png");
        m_Normal = new Morpheus::Texture("Assets/images/tileset_n.png");
        m_Specular = new Morpheus::Texture("Assets/images/tileset_s.png");

        m_TexturePlayer = new Morpheus::Texture("Assets/images/ash.png");
        m_NormalPlayer = new Morpheus::Texture("Assets/images/ash_n.png");
        m_SpecularPlayer = new Morpheus::Texture("Assets/images/ash_s.png");

        m_Tiles = Morpheus::MapLoader::load("Assets/maps/level_1/map_3.json");
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

        for (const auto& tile : m_Tiles)
        {
            m_SpriteRenderer->Draw(m_Texture, m_Normal, m_Specular, tile->destRect, tile->sourceRect, glm::vec4(1, 1, 1, 1));
        }

        m_SpriteRenderer->SetScale(zoom);

        //m_SpriteRenderer->SetAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.01f));

        m_SpriteRenderer->SetAmbientColor(ambienteColor);
        m_SpriteRenderer->EnableNormal(!inputState.SPACE);
        m_SpriteRenderer->EnableSpecular(!inputState.LEFT_CONTROL);
        m_SpriteRenderer->EnableWireframe(inputState.LEFT_SHIFT);

        //m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.4f, 3.0f, 20.0f));
        m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.01f, 1.0f, 20.0f));

        m_SpriteRenderer->Render();

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

        m_SpriteRenderer->Draw(
            m_TexturePlayer,
            m_NormalPlayer,
            m_SpecularPlayer,
            destPlayerPos,
            spriteFrame,
            glm::vec4(1, 1, 1, 1)
        );

        //m_SpriteRenderer->AddSpotLight(glm::vec3(600.0, 400.0, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.1f, 1.0f, 900.0f));
        m_SpriteRenderer->AddSpotLight(glm::vec3(560.0, 300.0 - zoom, 0.01f), glm::vec4(1.0f, 0.8f, 0.6f, 1.0f), glm::vec3(0.01f, 1.0f, 20.0f));

        m_SpriteRenderer->Render();
    }

    void GameApp::FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate)
    {
    }

}
