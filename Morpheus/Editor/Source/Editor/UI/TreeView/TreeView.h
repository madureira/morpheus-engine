#pragma once

#include "Editor/UI/UIComponent.h"

#include <string>
#include <map>

namespace Editor {

	class TreeView : public UIComponent
	{
	private:
		std::map<int, bool> m_TreeState;

	public:
		TreeView();
		void Draw(entt::registry& registry) override;

	private:
		bool CreateFolderNode(int nodeIndex, std::string nodeTitle);
		void CreateFileNode(int nodeIndex, std::string nodeTitle);
		std::string BuildFolderTitle(std::string title, bool isOpened);
		std::string BuildFileTitle(std::string title);
	};

}
