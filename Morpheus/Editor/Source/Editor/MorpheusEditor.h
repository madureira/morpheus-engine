#pragma once

#include "Engine/App.h"
#include "Engine/Config/Settings.h"
#include "Engine/Event/EventBus.h"
#include "Engine/Window/Window.h"
#include "Editor/UI/Menubar/Menubar.h"
#include "Editor/UI/Actionbar/Actionbar.h"
#include "Editor/UI/Dock/Dock.h"

namespace Editor {

	class MorpheusEditor : public Morpheus::App
	{
	private:
		Morpheus::Settings* m_Settings;
		Morpheus::EventBus* m_EventBus;
		Morpheus::Window* m_Window;
		Menubar* m_Menubar;
		Actionbar* m_Actionbar;
		Dock* m_Dock;

	public:
		MorpheusEditor();
		~MorpheusEditor();
		void Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus, Morpheus::Window* pWindow) override;
		void OnFrameStarted(double deltaTime, int frame, entt::registry& registry) override;
		void FrameListener(double deltaTime, int frame, entt::registry& registry) override;
	};

}
