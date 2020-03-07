#pragma once

#include "Editor/UI/UIContainer.h"
#include "Editor/UI/Components/CodeEditor/CodeEditor.h"
#include "TreeView/TreeView.h"
#include "Preview/Preview.h"
#include <string>

namespace Editor {

	class Project : public UIContainer
	{
	private:
		Preview* m_Preview;
		TreeView* m_TreeView;
		CodeEditor* m_CodeEditor;
		std::string m_ProjectPath;
		std::string m_CurrentFolderSelected;
		std::string m_CurrentFileSelected;

	public:
		Project(entt::registry& registry);
		~Project();

		void Draw(entt::registry& registry) override;

	private:
		void UpdateProjectPath(Morpheus::ProjectComponent& projectComponent);
		void OpenCodeEditor(entt::registry& registry);
	};

}
