#pragma once

#include "Editor/UI/UIComponent.h"
#include "Editor/UI/TreeView/TreeView.h"
#include <string>

namespace Editor {

	class Project : public UIComponent
	{
	private:
		std::string m_ProjectPath;
		TreeView* m_TreeView;

	public:
		Project(entt::registry& registry);
		void Draw(entt::registry& registry) override;

	private:
		void UpdateProjectPath(entt::registry& registry);
	};

}
