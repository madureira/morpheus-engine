#pragma once

#include <Engine/App.h>
#include <Engine/Window/Window.h>
#include "Editor/UI/Menubar/Menubar.h"
#include "Editor/UI/Actionbar/Actionbar.h"
#include "Editor/UI/Dock/Dock.h"
#include "Editor/UI/Footer/Footer.h"

namespace Editor {

	class MorpheusEditor : public Morpheus::App
	{
	private:
		Menubar* m_Menubar;
		Actionbar* m_Actionbar;
		Dock* m_Dock;
		Footer* m_Footer;

	public:
		MorpheusEditor();
		~MorpheusEditor();

		void Initialize(entt::registry& registry) override;
		void OnFrameStarted(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) override;
		void FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) override;
	};

}
