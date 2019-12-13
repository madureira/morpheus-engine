#pragma once

#include "Editor/UI/UIComponent.h"
#include "./NewProject/NewProject.h"

namespace Editor {

	class Menubar : public UIComponent
	{
	private:
		NewProject* m_NewProject;

	public:
		void Draw(entt::registry& registry) override;
	};

}
