#pragma once

#include "Editor/Containers/UIContainer.h"
#include <Engine/Util/JSON.h>
#include <functional>
#include <string>
#include <map>

namespace Editor {

	class TreeView final : public UIContainer
	{
	private:
		Morpheus::JSON m_JSON;
		std::map<std::string, bool> m_TreeState;
		std::function<void(std::string& path)> m_HandleFolderSelection;
		std::function<void(std::string & path)> m_HandleFileSelection;

	public:
		TreeView(std::string& currentPath, std::function<void(std::string & path)> onFolderSelect, std::function<void(std::string & path)> onFileSelect);

		void Render(entt::registry& registry) override;

	private:
		void RenderFileTree(Morpheus::JSON& tree);
		bool CreateFolderNode(std::string nodeIndex, std::string nodeTitle);
		void CreateFileNode(std::string nodeIndex, std::string nodeTitle, std::string fileExtension);
		std::string BuildFolderTitle(std::string& title, bool isOpened);
		std::string BuildFileTitle(std::string& title, std::string& fileExtension);
	};

}
