#pragma once

#include "Editor/Containers/UIContainer.h"
#include "./NewProject/NewProject.h"
#include "./NewScene/NewScene.h"

namespace Editor {

	class Menubar final : public UIContainer
	{
	private:
		NewProject* m_NewProject;
		NewScene* m_NewScene;

	public:
		Menubar();
		~Menubar();

		void Render(entt::registry& registry) override;
	};

}
