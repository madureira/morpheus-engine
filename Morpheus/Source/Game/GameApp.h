#pragma once

#include "Core/App.h"
#include "Core/Event/EventBus.h"
#include "Core/Shader/Shader.h"
#include "Core/Texture/Texture.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	private:
		unsigned int VBO, VAO, EBO;
		Morpheus::EventBus* m_EventBus;
		Morpheus::Shader* m_Shader;
		Morpheus::Texture* m_Texture;

	public:
		~GameApp();
		void Initialize(Morpheus::EventBus* eventBus) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;
	};

}
