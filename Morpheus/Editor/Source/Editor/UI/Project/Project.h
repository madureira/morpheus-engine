#pragma once

#include "Editor/UI/UIComponent.h"
#include "TreeView/TreeView.h"
#include "Preview/Preview.h"
#include <string>

namespace Editor {

	class Project : public UIComponent
	{
	private:
		std::string m_ProjectPath;
		TreeView* m_TreeView;
		Preview* m_Preview;
		std::string m_CurrentFolderSelected;
		std::string m_CurrentFileSelected;

	public:
		Project(entt::registry& registry);
		void Draw(entt::registry& registry) override;

	private:
		void UpdateProjectPath(entt::registry& registry);
	};

}
