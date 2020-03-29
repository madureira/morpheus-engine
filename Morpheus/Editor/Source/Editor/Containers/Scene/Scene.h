#pragma once

#include <glm/vec4.hpp>
#include <Engine/Shader/Shader.h>
#include <Engine/Texture/Texture.h>
#include <Engine/Renderer/SpriteRenderer.h>
#include "Editor/Containers/UIContainer.h"

namespace Editor {

	constexpr int CHECKERBOARD_INTENSITY = 140;

	class Scene final : public UIContainer
	{
	private:
		int m_InitialWindowWidth;
		int m_InitialWindowHeight;
		unsigned int m_FBO;
		unsigned int m_TextureColorBuffer;
		unsigned int m_CheckerboardTextureID;
		glm::vec4 m_FrameBufferRect;

		// App member variables
		float m_Vertices[9];
		unsigned int m_VAO;
		unsigned int m_VBO;
		Morpheus::Shader* m_Shader;
		Morpheus::SpriteRenderer* m_SpriteRenderer;
		Morpheus::Texture* m_Texture;
		Morpheus::Texture* m_Normal;
		Morpheus::Texture* m_Specular;
		Morpheus::Texture* m_TexturePlayer;
		Morpheus::Texture* m_NormalPlayer;
		Morpheus::Texture* m_SpecularPlayer;
		Morpheus::Texture* m_TextureHexagon;
		Morpheus::Texture* m_NormalHexagon;
		Morpheus::Texture* m_SpecularHexagon;

	public:
		Scene(entt::registry& registry);
		~Scene();

		void Render(entt::registry& registry) override;

	private:
		void InitializeApp(entt::registry& registry);
		void UpdateApp(entt::registry& registry);
		void ShutdownApp();
		void ClearViewport(entt::registry& registry);
		void RenderViewport(entt::registry& registry);
		void GenerateCheckerboardImage();
		void GenerateTextureBuffer();
		glm::vec4 getTile(int tileSize, int layer);
	};

}
