#include "TreeView.h"

namespace Editor {

	TreeView::TreeView()
	{
		this->m_TreeState[1] = false;
		this->m_TreeState[2] = false;
	}

	void TreeView::Draw(entt::registry& registry)
	{
		static int nodeClicked = -1;

		static int node1 = 1;
		static int node2 = 2;

		bool nodeOpened = this->CreateFolderNode(node1, "Root");

		if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
		{
			nodeClicked = node1;
		}

		if (nodeOpened)
		{
			this->m_TreeState[node1] = true;

			nodeOpened = this->CreateFolderNode(node2, "Child");

			if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
			{
				nodeClicked = node2;
			}

			if (nodeOpened)
			{
				this->m_TreeState[node2] = true;

				this->CreateFileNode(3, "File.h");
				this->CreateFileNode(4, "File.cpp");

				ImGui::TreePop();
			}
			else
			{
				this->m_TreeState[node2] = false;
			}

			ImGui::TreePop();
		}
		else
		{
			this->m_TreeState[1] = false;
		}
	}

	bool TreeView::CreateFolderNode(int nodeIndex, std::string nodeTitle)
	{
		nodeTitle = this->BuildFolderTitle(nodeTitle, this->m_TreeState[nodeIndex]);
		return ImGui::TreeNodeEx((void*)(intptr_t)nodeIndex, ImGuiTreeNodeFlags_None, nodeTitle.c_str(), nodeIndex);
	}

	void TreeView::CreateFileNode(int nodeIndex, std::string nodeTitle)
	{
		ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		nodeTitle = this->BuildFileTitle(nodeTitle);
		ImGui::TreeNodeEx((void*)(intptr_t)nodeIndex, nodeFlags, nodeTitle.c_str(), nodeIndex);
	}

	std::string TreeView::BuildFolderTitle(std::string title, bool isOpened)
	{
		std::string nodeTitle = isOpened ? ICON_FA_FOLDER_OPEN : ICON_FA_FOLDER;
		nodeTitle += "  ";
		nodeTitle += title;

		return nodeTitle;
	}

	std::string TreeView::BuildFileTitle(std::string title)
	{
		std::string nodeTitle = ICON_FA_FILE_CODE;
		nodeTitle += "  ";
		nodeTitle += title;

		return nodeTitle;
	}

}
