#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/ECS/ECS.h"

namespace Editor {

	class Viewport;
	class Project;
	class Console;
	class Hierarchy;
	class Inspector;

	class Dock : public UIComponent
	{
	private:
		Viewport* m_Viewport;
		Project* m_Project;
		Console* m_Console;
		Hierarchy* m_Hierarchy;
		Inspector* m_Inspector;

	public:
		Dock(entt::registry& registry);
		~Dock();
		void Draw(entt::registry& registry) override;
	};

}
