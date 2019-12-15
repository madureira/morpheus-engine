#include "TreeView.h"
#include "Engine/Util/FileUtil.h"

#include <fstream>
#include <iostream>

namespace Editor {

	TreeView::TreeView(std::string& path)
		: m_JSON(nullptr)
	{
		this->m_JSON = json::parse(Morpheus::FileUtil::ReadDirectoryTreeAsJsonString(path));
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
				ME_LOG_INFO("Folder path: {0}", tree["path"]);
			}

			if (this->m_TreeState[tree["path"]])
			{
				for (auto& node : tree["children"])
				{
					this->DrawFileTree(node);
				}
				ImGui::TreePop();
			}
		}
		else
		{
			this->CreateFileNode(tree["path"], tree["name"]);

			if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
			{
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

	void TreeView::CreateFileNode(std::string nodeIndex, std::string nodeTitle)
	{
		nodeTitle = this->BuildFileTitle(nodeTitle);
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

	std::string TreeView::BuildFileTitle(std::string& title)
	{
		std::string nodeTitle = ICON_FA_FILE_CODE;
		nodeTitle += "  ";
		nodeTitle += title;
		return nodeTitle;
	}

}
