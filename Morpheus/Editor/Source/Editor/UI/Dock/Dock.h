#pragma once

#include "Engine/Config/Settings.h"
#include "Editor/UI/UIComponent.h"
#include "Editor/UI/Viewport/Viewport.h"
#include "Editor/UI/ColorPicker/ColorPicker.h"

namespace Editor {

	class Dock : public UIComponent
	{
	private:
		Viewport* m_Viewport;
		ColorPicker* m_ColorPicker;

	public:
		Dock(Morpheus::Settings* pSettings);
		~Dock();
		void Draw() override;
	};

}
