#include "TreeView.h"
#include <algorithm>
#include <Engine/Util/FileUtil.h>

namespace Editor {

	TreeView::TreeView(std::string& currentPath, std::function<void(std::string & path)> onFolderSelect, std::function<void(std::string & path)> onFileSelect)
		: m_JSON(nullptr)
		, m_HandleFolderSelection(onFolderSelect)
		, m_HandleFileSelection(onFileSelect)
	{
		this->m_JSON = Morpheus::JSON::parse(Morpheus::FileUtil::ReadDirectoryTreeAsJsonString(currentPath));
	}

	void TreeView::Render(entt::registry& registry)
	{
		this->RenderFileTree(this->m_JSON);
	}

	void TreeView::RenderFileTree(Morpheus::JSON& tree)
	{
		if (tree["type"] == "folder")
		{
			if (this->m_TreeState.find(tree["path"]) == this->m_TreeState.end())
			{
				this->m_TreeState[tree["path"]] = false;
			}

			this->m_TreeState[tree["path"]] = this->CreateFolderNode(tree["path"], tree["name"]);

			if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
			{
				std::string folderPath(tree["path"]);
				this->m_HandleFolderSelection(folderPath);
				ME_LOG_INFO("Folder path: {0}", folderPath);
			}

			if (this->m_TreeState[tree["path"]])
			{
				std::sort(tree["children"].begin(), tree["children"].end(), [](const Morpheus::JSON& a, const Morpheus::JSON& b) {
					if (a["type"] == "folder" && b["type"] == "folder")
					{
						return a["name"] < b["name"];
					}

					return a["type"] == "folder" && b["type"] != "folder";
				});

				for (auto& node : tree["children"])
				{
					this->RenderFileTree(node);
				}
				ImGui::TreePop();
			}
		}
		else
		{
			this->CreateFileNode(tree["path"], tree["name"], tree["extension"]);

			std::string filePath(tree["path"]);

			if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
			{
				ME_LOG_INFO("File size: {0}", tree["size"]);
			}

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{
				this->m_HandleFileSelection(filePath);
			}
		}
	}

	bool TreeView::CreateFolderNode(std::string nodeIndex, std::string nodeTitle)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		return ImGui::TreeNodeEx(this->BuildFolderTitle(nodeTitle, this->m_TreeState[nodeIndex]).c_str(), flags);
	}

	void TreeView::CreateFileNode(std::string nodeIndex, std::string nodeTitle, std::string fileExtension)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(this->BuildFileTitle(nodeTitle, fileExtension).c_str(), flags);
	}

	std::string TreeView::BuildFolderTitle(std::string& title, bool isOpened)
	{
		std::string nodeTitle(isOpened ? ICON_FA_FOLDER_OPEN : ICON_FA_FOLDER);
		nodeTitle += "  " + title + "###" + title;
		return nodeTitle;
	}

	std::string TreeView::BuildFileTitle(std::string& title, std::string& fileExtension)
	{
		std::string nodeTitle = ICON_FA_FILE;

		if (Morpheus::Extension::IsImage(fileExtension))
		{
			nodeTitle = ICON_FA_FILE_IMAGE;
		}

		if (Morpheus::Extension::IsCode(fileExtension) || Morpheus::Extension::IsShader(fileExtension))
		{
			nodeTitle = ICON_FA_FILE_CODE;
		}

		if (Morpheus::Extension::IsData(fileExtension))
		{
			nodeTitle = ICON_FA_DATABASE;
		}

		if (Morpheus::Extension::IsFont(fileExtension))
		{
			nodeTitle = ICON_FA_FONT;
		}

		if (Morpheus::Extension::IsScene(fileExtension))
		{
			nodeTitle = ICON_FA_CUBE;
		}

		nodeTitle += "  ";
		nodeTitle += title;
		return nodeTitle;
	}

}
