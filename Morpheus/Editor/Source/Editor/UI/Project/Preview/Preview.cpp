#include "Preview.h"
#include "Engine/Util/FileUtil.h"
#include <iostream>

namespace Editor {

	Preview::Preview()
		: m_JSON(nullptr),
		m_CurrentFolder(""),
		m_CurrentFiles(""),
		m_FolderIcon(nullptr),
		m_FileIcon(nullptr),
		m_Zoom(1)
	{
		this->m_FolderIcon = new Morpheus::Texture("Assets/icons/black-folder-icon.png");
		this->m_FileIcon = new Morpheus::Texture("Assets/icons/document-icon.png");
	}

	Preview::~Preview()
	{
		for (auto image : this->m_Images)
		{
			delete image.second;
		}
	}

	void Preview::Draw(entt::registry& registry)
	{
		ImVec2 winSize = ImGui::GetContentRegionAvail();

		ImGui::BeginChild("preview_region", ImVec2(0, winSize.y - 30), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImVec2 areaSize = ImGui::GetContentRegionAvail();

			static int margin = 10;
			static int imageSize = 64;
			int width = margin;

			ImGui::Dummy(ImVec2(0, margin));

			for (auto &image : this->m_Images)
			{
				ImGui::Dummy(ImVec2(margin, 0));
				ImGui::SameLine();

				ImGui::BeginGroup();
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0, 0)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0.25f, 0.25f, 0.25f, 1.00f)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(150, 150, 150)));
				ImGui::ImageButton((void*)image.second->GetID(), ImVec2(imageSize * this->m_Zoom, imageSize * this->m_Zoom));
				ImGui::PopStyleColor(3);
				ImGui::Dummy(ImVec2(0, 5));
				ImGui::Dummy(ImVec2(5, 0));
				ImGui::SameLine();
				std::string truncatedText(this->TruncateFileName(image.first));
				ImVec2 textSize = ImGui::CalcTextSize(truncatedText.c_str());
				ImVec2 pos = ImGui::GetCursorPos();
				pos.x += (imageSize * this->m_Zoom - textSize.x) * 0.5f;
				ImGui::SetCursorPos(pos);
				ImGui::Text(truncatedText.c_str());
				ImGui::EndGroup();

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextUnformatted(image.first.c_str());
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
			}
		}
		ImGui::EndChild();

		this->DrawZoomButtons(winSize.x);
	}

	void Preview::UpdateSelectedFolder(std::string& folderPath)
	{
		if (this->m_CurrentFolder != folderPath)
		{
			this->m_CurrentFolder = folderPath;
			this->m_JSON = json::parse(Morpheus::FileUtil::ReadDirectoryAsJsonString(this->m_CurrentFolder));

			for (auto image : this->m_Images)
			{
				if (image.second != this->m_FolderIcon && image.second != this->m_FileIcon)
				{
					delete image.second;
				}
			}
			this->m_Images.clear();

			for (auto node : this->m_JSON)
			{
				std::string nodePath(node["path"]);
				std::string nodeName(node["name"]);
				if (node["type"] == "file")
				{
					if (Morpheus::Extension::IsImage(node["extension"]))
					{
						this->m_Images[nodeName] = new Morpheus::Texture(nodePath.c_str());
					}
					else
					{
						this->m_Images[nodeName] = this->m_FileIcon;
					}
				}
				else if (node["type"] == "folder")
				{
					this->m_Images[nodeName] = this->m_FolderIcon;
				}
			}
		}
	}

	void Preview::UpdateSelectedFile(std::string& filePath)
	{
		this->m_CurrentFiles = filePath;
	}

	void Preview::DrawZoomButtons(float areaWidth)
	{
		ImGui::BeginChild("slide_region", ImVec2(0, 30), false);
		{
			ImGui::Indent(areaWidth - 58);
			ImGui::Dummy(ImVec2(0, 3));
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
