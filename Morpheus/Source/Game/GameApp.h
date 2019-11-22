#pragma once

#include <glad/glad.h>
#include "Config/Settings.h"
#include "Core/App.h"
#include "Core/Event/EventBus.h"
#include "Core/Shader/Shader.h"
#include "Core/Texture/Texture.h"
#include "Core/Renderer/SpriteBatcher.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	private:
		Morpheus::Settings* m_Settings;
		Morpheus::EventBus* m_EventBus;
		Morpheus::Shader* m_Shader;
		Morpheus::Texture* m_Texture;
		Morpheus::SpriteBatcher* m_SpriteBatcher;

	public:
		~GameApp();
		void Initialize(Morpheus::EventBus* pEventBus, Morpheus::Settings* pSettings) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;

	private:
		glm::vec4 getTile(int tileSize, int layer);
	};

}
