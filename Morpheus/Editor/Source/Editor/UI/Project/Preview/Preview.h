#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/Texture/Texture.h"
#include <nlohmann/json.hpp>
#include <string>
#include <map>

namespace Editor {

	using json = nlohmann::json;

	class Preview : public UIComponent
	{
	private:
		json m_JSON;
		std::string m_CurrentFolder;
		std::string m_CurrentFiles;
		std::map<std::string, Morpheus::Texture*> m_Images;
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
		void DrawZoomButtons(float areaWidth);
		std::string TruncateFileName(std::string fileName);
	};

}
