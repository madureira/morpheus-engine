#pragma once

#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <Engine/Util/JSON.h>
#include <Engine/Texture/Texture.h>
#include "Editor/Containers/UIContainer.h"

namespace Editor {

	using json = nlohmann::json;

	struct PreviewItem final
	{
		std::string title;
		Morpheus::Texture* image;
		Morpheus::JSON data;

		PreviewItem(std::string title_, Morpheus::Texture* image_, Morpheus::JSON data_)
			: title(title_)
			, image(image_)
			, data(data_)
		{
		}
	};

	class Preview final : public UIContainer
	{
	private:
		json m_JSON;
		std::string m_CurrentFolder;
		std::string m_CurrentFile;
		std::string m_SelectedItem;
		std::vector<PreviewItem*> m_Items;
		Morpheus::Texture* m_FolderIcon;
		Morpheus::Texture* m_FileIcon;
		Morpheus::Texture* m_SceneIcon;
		int m_Zoom;
		std::function<void(std::string& path)> m_HandleFolderSelection;
		std::function<void(std::string& path)> m_HandleFileSelection;

	public:
		Preview(std::function<void(std::string& path)> onFolderSelect, std::function<void(std::string& path)> onFileSelect);
		~Preview();

		void Render(entt::registry& registry) override;
		void UpdateSelectedFolder(std::string& folderPath);
		void UpdateSelectedFile(std::string& filePath);

	private:
		void Shutdown();
		void DrawFooter(float areaWidth);
		std::string TruncateFileName(std::string fileName);
	};

}
