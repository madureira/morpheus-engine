#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/Window/Window.h"

namespace Editor {

	class Menubar : public UIComponent
	{
	private:
		Morpheus::Window* m_Window;

	public:
		Menubar(Morpheus::Window* pWindow);
		void Draw() override;
	};

}
