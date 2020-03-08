#pragma once

#include "Editor/Containers/UIContainer.h"
#include <Engine/ECS/ECS.h>

namespace Editor {

	class Scene;
	class Project;
	class Console;
	class Hierarchy;
	class Inspector;

	class Dock : public UIContainer
	{
	private:
		Scene* m_Scene;
		Project* m_Project;
		Console* m_Console;
		Hierarchy* m_Hierarchy;
		Inspector* m_Inspector;

	public:
		Dock(entt::registry& registry);
		~Dock();

		void Render(entt::registry& registry) override;
	};

}
