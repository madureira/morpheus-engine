#pragma once

#include "Engine/App.h"
#include "Engine/Config/Settings.h"
#include "Engine/Event/EventBus.h"
#include "Engine/Window/Window.h"

namespace Editor {

	class EditorApp : public Morpheus::App
	{
	private:
		Morpheus::Settings* m_Settings;
		Morpheus::EventBus* m_EventBus;
		Morpheus::Window* m_Window;

	public:
		~EditorApp();
		void Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus, Morpheus::Window* pWindow) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;
	};

}
