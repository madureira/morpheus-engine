#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/Texture/Texture.h"
#include <nlohmann/json.hpp>
#include <string>
#include <map>
#include <utility>

namespace Editor {

	using json = nlohmann::json;

	class Preview : public UIComponent
	{
	private:
		json m_JSON;
		std::string m_CurrentFolder;
		std::string m_CurrentFile;
		std::string m_SelectedItem;
		std::map<std::string, std::pair<json, Morpheus::Texture*>> m_Items;
		Morpheus::Texture* m_FolderIcon;
		Morpheus::Texture* m_FileIcon;
		int m_Zoom;

	public:
		Preview();
		~Preview();
		void Draw(entt::registry& registry) override;
		void UpdateSelectedFolder(std::string& folderPath);
		void UpdateSelectedFile(std::string& filePath);

	private:
		void Shutdown();
		void DrawFooter(float areaWidth);
		std::string TruncateFileName(std::string fileName);
	};

}
