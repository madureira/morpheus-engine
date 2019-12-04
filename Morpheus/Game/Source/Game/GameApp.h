#pragma once

#include "Engine/App.h"
#include "Engine/Config/Settings.h"
#include "Engine/Event/EventBus.h"
#include "Engine/Window/Window.h"
#include "Engine/Event/Types/InputEvent.h"
#include "Engine/Renderer/SpriteRenderer.h"
#include "Engine/Texture/Texture.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	private:
		Morpheus::Settings* m_Settings;
		Morpheus::EventBus* m_EventBus;
		Morpheus::SpriteRenderer* m_SpriteRenderer;
		Morpheus::InputState m_InputState;
		Morpheus::Texture* m_Texture;
		Morpheus::Texture* m_Normal;

		Morpheus::Texture* m_TexturePlayer;
		Morpheus::Texture* m_NormalPlayer;

	public:
		GameApp();
		~GameApp();
		void Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus, Morpheus::Window* pWindow) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;

	private:
		void InputHandler(Morpheus::InputEvent* pEvent);
		glm::vec4 getTile(int tileSize, int layer);
	};

}
