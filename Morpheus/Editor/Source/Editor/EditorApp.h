#pragma once

#include "Core/App.h"
#include "Core/Config/Settings.h"
#include "Core/Event/EventBus.h"
#include "Core/Window/Window.h"

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
