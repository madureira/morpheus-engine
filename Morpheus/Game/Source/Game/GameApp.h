#pragma once

#include <Engine/App.h>
#include <Engine/Renderer/SpriteRenderer.h>
#include <Engine/Texture/Texture.h>
#include <Engine/Util/MapLoader.h>
#include <vector>

namespace Game {

	class GameApp final : public Morpheus::App
	{
	private:
		int m_InitialWindowWidth;
		int m_InitialWindowHeight;
		Morpheus::SpriteRenderer* m_SpriteRenderer;
		Morpheus::Texture* m_Texture;
		Morpheus::Texture* m_Normal;
		Morpheus::Texture* m_Specular;
		Morpheus::Texture* m_TexturePlayer;
		Morpheus::Texture* m_NormalPlayer;
		Morpheus::Texture* m_SpecularPlayer;
		std::vector<Morpheus::Tile*> m_Tiles;

	public:
		GameApp();
		~GameApp();

		void Initialize(entt::registry& registry) override;
		void OnFrameStarted(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) override;
		void FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) override;
	};

}
