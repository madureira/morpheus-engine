#pragma once

#include "Editor/UI/UIComponent.h"

#include <nlohmann/json.hpp>
#include <string>
#include <map>
#include <filesystem>

namespace Editor {

	namespace fs = std::filesystem;
	using json = nlohmann::json;

	class TreeView : public UIComponent
	{
	private:
		std::map<std::string, bool> m_TreeState;
		json m_JSON;

	public:
		TreeView(std::string& path);
		void Draw(entt::registry& registry) override;

	private:
		void DrawFileTree(json& tree);
		bool CreateFolderNode(std::string nodeIndex, std::string nodeTitle);
		void CreateFileNode(std::string nodeIndex, std::string nodeTitle);
		std::string BuildFolderTitle(std::string& title, bool isOpened);
		std::string BuildFileTitle(std::string& title);
	};

}
