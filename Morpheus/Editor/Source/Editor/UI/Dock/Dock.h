#pragma once

#include "Engine/Config/Settings.h"
#include "Editor/UI/UIComponent.h"
#include "Editor/UI/Viewport/Viewport.h"

namespace Editor {

	class Dock : public UIComponent
	{
	private:
		Viewport* m_Viewport;
	public:
		Dock(Morpheus::Settings* pSettings);
		~Dock();
		void Draw() override;
	};

}
