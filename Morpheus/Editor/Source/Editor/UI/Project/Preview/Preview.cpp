#include "Preview.h"
#include "Engine/Util/FileUtil.h"
#include <iostream>

namespace Editor {

	Preview::Preview()
		: m_JSON(nullptr)
		, m_CurrentFolder("")
		, m_CurrentFile("")
		, m_SelectedItem("")
		, m_FolderIcon(nullptr)
		, m_FileIcon(nullptr)
		, m_Zoom(1)
	{
		this->m_FolderIcon = new Morpheus::Texture("Assets/icons/black-folder-icon.png");
		this->m_FileIcon = new Morpheus::Texture("Assets/icons/document-icon.png");
	}

	Preview::~Preview()
	{
		for (auto image : this->m_Items)
		{
			delete image.second.second;
		}
	}

	void Preview::Draw(entt::registry& registry)
	{
		ImVec2 winSize = ImGui::GetContentRegionAvail();

		ImGui::BeginChild("preview_region", ImVec2(0, winSize.y - 35), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImVec2 areaSize = ImGui::GetContentRegionAvail();

			static int margin = 10;
			static int imageSize = 64;
			int width = margin;

			ImGui::Dummy(ImVec2(0, margin));

			int itemId = 0;
			for (auto &item : this->m_Items)
			{
				ImGui::Dummy(ImVec2(margin, 0));
				ImGui::SameLine();

				ImGui::BeginGroup();
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0, 0)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0.25f, 0.25f, 0.25f, 1.00f)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(150, 150, 150)));
				ImGui::PushID(itemId);
				if (ImGui::ImageButton((void*)item.second.second->GetID(), ImVec2(imageSize * this->m_Zoom, imageSize * this->m_Zoom)))
				{
					this->m_SelectedItem = item.second.first["path"].get<std::string>();
				}
				ImGui::PopID();
				ImGui::PopStyleColor(3);
				ImGui::Dummy(ImVec2(0, 5));
				ImGui::Dummy(ImVec2(5, 0));
				ImGui::SameLine();
				std::string truncatedText(this->TruncateFileName(item.first));
				ImVec2 textSize = ImGui::CalcTextSize(truncatedText.c_str());
				ImVec2 pos = ImGui::GetCursorPos();
				pos.x += (imageSize * this->m_Zoom - textSize.x) * 0.5f;
				ImGui::SetCursorPos(pos);
				ImGui::Text(truncatedText.c_str());
				ImGui::EndGroup();

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextUnformatted(item.first.c_str());
					ImGui::EndTooltip();
				}
			
				int nextSize = width + (margin * 3) + (imageSize * this->m_Zoom);

				if (areaSize.x > nextSize)
				{
					width = nextSize;
					ImGui::SameLine();
				}
				else
				{
					width = 0;
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(margin, 0));
					ImGui::Dummy(ImVec2(0, margin+3));
				}

				itemId++;
			}
		}
		ImGui::EndChild();

		this->DrawFooter(winSize.x);
	}

	void Preview::UpdateSelectedFolder(std::string& folderPath)
	{
		if (this->m_CurrentFolder != folderPath)
		{
			this->m_SelectedItem = "";
			this->m_CurrentFolder = folderPath;
			this->m_JSON = json::parse(Morpheus::FileUtil::ReadDirectoryAsJsonString(this->m_CurrentFolder));

			for (auto image : this->m_Items)
			{
				if (image.second.second != this->m_FolderIcon && image.second.second != this->m_FileIcon)
				{
					image.second.first.clear();
					delete image.second.second;
				}
			}
			this->m_Items.clear();

			for (auto node : this->m_JSON)
			{
				json currentNode;
				currentNode["name"] = node["name"];
				currentNode["path"] = node["path"];
				currentNode["type"] = node["type"];

				std::string nodeName(currentNode["name"]);
				if (currentNode["type"] == "file")
				{
					currentNode["extension"] = node["extension"];
					currentNode["size"] = node["size"];

					if (Morpheus::Extension::IsImage(currentNode["extension"]))
					{
						this->m_Items[nodeName] = std::make_pair(currentNode, new Morpheus::Texture(currentNode["path"].get<std::string>().c_str()));
					}
					else
					{
						this->m_Items[nodeName] = std::make_pair(currentNode, this->m_FileIcon);
					}
				}
				else if (currentNode["type"] == "folder")
				{
					this->m_Items[nodeName] = std::make_pair(currentNode, this->m_FolderIcon);
				}
			}
		}
	}

	void Preview::UpdateSelectedFile(std::string& filePath)
	{
		this->m_CurrentFile = filePath;
	}

	void Preview::DrawFooter(float areaWidth)
	{
		ImGui::BeginChild("slide_region", ImVec2(0, 35), false);
		{
			ImVec2 generalPos = ImGui::GetCursorPos();
			generalPos.y += 5;
			ImGui::SetCursorPos(generalPos);

			ImGui::BeginChild("text_region", ImVec2(areaWidth - 65, 0), false);
			{
				ImVec2 pos = ImGui::GetCursorPos();
				pos.y += 5;
				pos.x += 10;
				ImGui::SetCursorPos(pos);
				ImGui::Text(this->m_SelectedItem.c_str());
			}
			ImGui::EndChild();

			ImGui::SameLine();
			ImGui::Dummy(ImVec2(4, 0));
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_SEARCH_PLUS))
			{
				if (this->m_Zoom < 3)
				{
					this->m_Zoom++;
				}
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(3, 0));
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_SEARCH_MINUS))
			{
				if (this->m_Zoom > 1)
				{
					this->m_Zoom--;
				}
			}
		}
		ImGui::EndChild();
	}

	std::string Preview::TruncateFileName(std::string fileName)
	{
		static const int SLOT_SIZE = 8;

		if (fileName.size() > SLOT_SIZE * this->m_Zoom)
		{
			return fileName.substr(0, SLOT_SIZE * this->m_Zoom) + "...";
		}

		return fileName;
	}

}
