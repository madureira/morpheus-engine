#pragma once

#include "Editor/Containers/UIContainer.h"
#include "./NewProject/NewProject.h"

namespace Editor {

	class Menubar final : public UIContainer
	{
	private:
		NewProject* m_NewProject;

	public:
		Menubar();
		~Menubar();

		void Render(entt::registry& registry) override;
	};

}
