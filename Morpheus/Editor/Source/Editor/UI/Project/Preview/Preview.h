#pragma once

#include "Editor/UI/UIComponent.h"
#include <Engine/Texture/Texture.h>
#include <nlohmann/json.hpp>
#include <functional>
#include <string>
#include <vector>
#include <utility>

namespace Editor {

	using json = nlohmann::json;

	struct PreviewItem
	{
		std::string title;
		Morpheus::Texture* image;
		json data;

		PreviewItem(std::string title_, Morpheus::Texture* image_, json data_)
			: title(title_)
			, image(image_)
			, data(data_)
		{
		}
	};

	class Preview : public UIComponent
	{
	private:
		json m_JSON;
		std::string m_CurrentFolder;
		std::string m_CurrentFile;
		std::string m_SelectedItem;
		std::vector<PreviewItem*> m_Items;
		Morpheus::Texture* m_FolderIcon;
		Morpheus::Texture* m_FileIcon;
		int m_Zoom;
		std::function<void(std::string& path)> m_HandleFolderSelection;
		std::function<void(std::string& path)> m_HandleFileSelection;

	public:
		Preview(std::function<void(std::string& path)> onFolderSelect, std::function<void(std::string& path)> onFileSelect);
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
