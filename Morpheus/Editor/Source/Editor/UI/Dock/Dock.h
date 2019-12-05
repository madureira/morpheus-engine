#pragma once

#include "Engine/Config/Settings.h"
#include "Editor/UI/UIComponent.h"
#include "Editor/UI/Viewport/Viewport.h"
#include "Editor/UI/ColorPicker/ColorPicker.h"
#include "Editor/UI/Project/Project.h"
#include "Editor/UI/Console/Console.h"
#include "Editor/UI/Hierarchy/Hierarchy.h"

namespace Editor {

	class Dock : public UIComponent
	{
	private:
		Viewport* m_Viewport;
		ColorPicker* m_ColorPicker;
		Project* m_Project;
		Console* m_Console;
		Hierarchy* m_Hierarchy;

	public:
		Dock(Morpheus::Settings* pSettings);
		~Dock();
		void Draw() override;
	};

}
