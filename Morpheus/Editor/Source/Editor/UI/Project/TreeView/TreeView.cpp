#include "TreeView.h"
#include "Engine/Util/FileUtil.h"
#include <algorithm>

namespace Editor {

	TreeView::TreeView(std::string& currentPath, std::function<void(std::string & path)> onFolderSelect, std::function<void(std::string & path)> onFileSelect)
		: m_JSON(nullptr)
		, m_HandleFolderSelection(onFolderSelect)
		, m_HandleFileSelection(onFileSelect)
	{
		this->m_JSON = json::parse(Morpheus::FileUtil::ReadDirectoryTreeAsJsonString(currentPath));
	}

	void TreeView::Draw(entt::registry& registry)
	{
		this->DrawFileTree(this->m_JSON);
	}

	void TreeView::DrawFileTree(json& tree)
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
				std::sort(tree["children"].begin(), tree["children"].end(), [](const json& a, const json& b) {
					if (a["type"] == "folder" && b["type"] == "folder")
					{
						return a["name"] < b["name"];
					}

					return a["type"] == "folder" && b["type"] != "folder";
				});

				for (auto& node : tree["children"])
				{
					this->DrawFileTree(node);
				}
				ImGui::TreePop();
			}
		}
		else
		{
			this->CreateFileNode(tree["path"], tree["name"], tree["extension"]);

			if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
			{
				std::string filePath(tree["path"]);
				this->m_HandleFileSelection(filePath);
				ME_LOG_INFO("File size: {0}", tree["size"]);
			}
		}
	}

	bool TreeView::CreateFolderNode(std::string nodeIndex, std::string nodeTitle)
	{
		nodeTitle = this->BuildFolderTitle(nodeTitle, this->m_TreeState[nodeIndex]);
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		return ImGui::TreeNodeEx(nodeTitle.c_str(), flags);
	}

	void TreeView::CreateFileNode(std::string nodeIndex, std::string nodeTitle, std::string fileExtension)
	{
		nodeTitle = this->BuildFileTitle(nodeTitle, fileExtension);
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(nodeTitle.c_str(), flags);
	}

	std::string TreeView::BuildFolderTitle(std::string& title, bool isOpened)
	{
		//std::string nodeTitle = isOpened ? ICON_FA_FOLDER_OPEN : ICON_FA_FOLDER;
		std::string nodeTitle = ICON_FA_FOLDER;
		nodeTitle += "  ";
		nodeTitle += title;
		return nodeTitle;
	}

	std::string TreeView::BuildFileTitle(std::string& title, std::string& fileExtension)
	{
		std::string nodeTitle = ICON_FA_FILE;

		if (Morpheus::Extension::IsImage(fileExtension))
		{
			nodeTitle = ICON_FA_FILE_IMAGE;
		}

		if (Morpheus::Extension::IsCode(fileExtension))
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

		nodeTitle += "  ";
		nodeTitle += title;
		return nodeTitle;
	}

}
