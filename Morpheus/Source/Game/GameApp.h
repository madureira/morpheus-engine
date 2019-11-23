#pragma once

#include "Core/App.h"
#include "Config/Settings.h"
#include "Core/Event/EventBus.h"
#include "Core/Event/Types/InputEvent.h"
#include "Core/Renderer/SpriteBatcher.h"
#include "Core/Texture/Texture.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	private:
		Morpheus::Settings* m_Settings;
		Morpheus::EventBus* m_EventBus;
		Morpheus::SpriteBatcher* m_SpriteBatcher;
		Morpheus::Texture* m_Texture;
		Morpheus::InputState m_InputState;

	public:
		~GameApp();
		void Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;

	private:
		void InputHandler(Morpheus::InputEvent* pEvent);
		glm::vec4 getTile(int tileSize, int layer);
	};

}
