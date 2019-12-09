#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/Config/Settings.h"

namespace Editor {

	class Viewport;
	class ColorPicker;
	class Project;
	class Console;
	class Hierarchy;

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
