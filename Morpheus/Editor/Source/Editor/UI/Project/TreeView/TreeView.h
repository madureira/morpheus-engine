#pragma once

#include "Editor/UI/UIComponent.h"
#include <nlohmann/json.hpp>
#include <functional>
#include <string>
#include <map>

namespace Editor {

	using json = nlohmann::json;

	class TreeView : public UIComponent
	{
	private:
		json m_JSON;
		std::map<std::string, bool> m_TreeState;
		std::function<void(std::string& path)> m_HandleFolderSelect;
		std::function<void(std::string & path)> m_HandleFileSelect;

	public:
		TreeView(std::string& currentPath, std::function<void(std::string & path)> onFolderSelect, std::function<void(std::string & path)> onFileSelect);
		void Draw(entt::registry& registry) override;

	private:
		void DrawFileTree(json& tree);
		bool CreateFolderNode(std::string nodeIndex, std::string nodeTitle);
		void CreateFileNode(std::string nodeIndex, std::string nodeTitle, std::string fileExtension);
		std::string BuildFolderTitle(std::string& title, bool isOpened);
		std::string BuildFileTitle(std::string& title, std::string& fileExtension);
	};

}
