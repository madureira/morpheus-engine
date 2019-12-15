#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/Shader/Shader.h"
#include <glm/vec4.hpp>

#include "Engine/Renderer/SpriteRenderer.h"
#include "Engine/Texture/Texture.h"

namespace Editor {

	class Viewport : public UIComponent
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		float m_Vertices[9];
		Morpheus::Shader* m_Shader;
		unsigned int m_FBO;
		unsigned int m_TextureColorBuffer;
		glm::vec4 m_FrameBufferRect;
		glm::vec4 m_Color;
		int m_InitialWindowWidth;
		int m_InitialWindowHeight;


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
		Viewport(entt::registry& registry);
		~Viewport();
		void ChangeColor(glm::vec4& color);
		void Draw(entt::registry& registry) override;

	private:
		glm::vec4 getTile(int tileSize, int layer);
	};

}
