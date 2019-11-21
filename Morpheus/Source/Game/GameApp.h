#pragma once

#include <glad/glad.h>
#include "Core/App.h"
#include "Core/Event/EventBus.h"
#include "Core/Shader/ShaderXXX.h"
#include "Core/Texture/TextureXXX.h"
#include "spriteBatcher.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		Morpheus::EventBus* m_EventBus;
		Morpheus::ShaderXXX* m_Shader;
		Morpheus::TextureXXX* m_Texture;
		SpriteBatcher* spriteBatcher;
		Texture* texture;

	public:
		~GameApp();
		void Initialize(Morpheus::EventBus* eventBus) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;

	private:
		glm::vec4 getTile(int tileSize, int layer);
	};

}
