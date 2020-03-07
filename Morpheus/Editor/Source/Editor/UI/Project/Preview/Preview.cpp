#include "Preview.h"
#include <Engine/Util/FileUtil.h>

namespace Editor {

	Preview::Preview(std::function<void(std::string& path)> onFolderSelect, std::function<void(std::string& path)> onFileSelect)
		: m_HandleFolderSelection(onFolderSelect)
		, m_HandleFileSelection(onFileSelect)
		, m_JSON(nullptr)
		, m_CurrentFolder("")
		, m_CurrentFile("")
		, m_SelectedItem("")
		, m_FolderIcon(new Morpheus::Texture("Assets/icons/black-folder-icon.png"))
		, m_FileIcon(new Morpheus::Texture("Assets/icons/document-icon.png"))
		, m_Zoom(1)
	{
	}

	Preview::~Preview()
	{
		this->Shutdown();
		delete this->m_FolderIcon;
		delete this->m_FileIcon;
	}

	void Preview::Draw(entt::registry& registry)
	{
		ImVec2 winSize = ImGui::GetContentRegionAvail();

		ImGui::BeginChild("preview_region", ImVec2(0, winSize.y - 35), false, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImVec2 areaSize = ImGui::GetContentRegionAvail();

			static float margin = 10.0f;
			static int imageSize = 64;
			float width = margin;

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
				if (ImGui::ImageButton((void*)item->image->GetID(), ImVec2((float)(imageSize * this->m_Zoom), (float)(imageSize * this->m_Zoom))))
				{
					this->m_SelectedItem = item->data["path"].get<std::string>();
				}

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
				{
					if (item->data["type"].get<std::string>() == "folder")
					{
						this->m_HandleFolderSelection(this->m_SelectedItem);
					}
					else if (item->data["type"].get<std::string>() == "file")
					{
						this->m_HandleFileSelection(this->m_SelectedItem);
					}
				}

				ImGui::PopID();
				ImGui::PopStyleColor(3);
				ImGui::Dummy(ImVec2(0, 5));
				ImGui::Dummy(ImVec2(5, 0));
				ImGui::SameLine();
				std::string truncatedText(this->TruncateFileName(item->title));
				ImVec2 textSize = ImGui::CalcTextSize(truncatedText.c_str());
				ImVec2 pos = ImGui::GetCursorPos();
				pos.x += (imageSize * this->m_Zoom - textSize.x) * 0.5f;
				ImGui::SetCursorPos(pos);
				ImGui::Text(truncatedText.c_str());
				ImGui::EndGroup();

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextUnformatted(item->title.c_str());
					ImGui::EndTooltip();
				}
			
				float nextSize = width + (margin * 3.0f) + (imageSize * this->m_Zoom);

				if (areaSize.x > nextSize)
				{
					width = nextSize;
					ImGui::SameLine();
				}
				else
				{
					width = 0.0f;
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(margin, 0));
					ImGui::Dummy(ImVec2(0, margin + 3.0f));
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

			this->Shutdown();

			for (auto node : this->m_JSON)
			{
				json currentNode;
				currentNode["name"] = node["name"];
				currentNode["path"] = node["path"];
				currentNode["type"] = node["type"];

				std::string itemKey(currentNode["name"]);
				if (currentNode["type"] == "file")
				{
					currentNode["extension"] = node["extension"];
					currentNode["size"] = node["size"];

					if (Morpheus::Extension::IsImage(currentNode["extension"]))
					{
						this->m_Items.push_back(
							new PreviewItem(
								currentNode["name"].get<std::string>(),
								new Morpheus::Texture(currentNode["path"].get<std::string>().c_str()),
								currentNode
							)
						);
					}
					else
					{
						this->m_Items.push_back(
							new PreviewItem(
								currentNode["name"].get<std::string>(),
								this->m_FileIcon,
								currentNode
							)
						);
					}
				}
				else if (currentNode["type"] == "folder")
				{
					this->m_Items.push_back(
						new PreviewItem(
							currentNode["name"].get<std::string>(),
							this->m_FolderIcon,
							currentNode
						)
					);
				}
			}

			std::sort(this->m_Items.begin(), this->m_Items.end(), [](const PreviewItem* a, const PreviewItem* b) {
				if (a->data["type"] == "folder" && b->data["type"] == "folder")
				{
					return a->title < b->title;
				}

				return a->data["type"] == "folder" && b->data["type"] != "folder";
			});
		}
	}

	void Preview::UpdateSelectedFile(std::string& filePath)
	{
		this->m_CurrentFile = filePath;
	}

	void Preview::Shutdown()
	{
		for (auto item : this->m_Items)
		{
			if (item->image != this->m_FileIcon && item->image != this->m_FolderIcon)
			{
				delete item->image;
			}
			delete item;
		}
		this->m_Items.clear();
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
			if (ImGui::Button(ICON_FA_SEARCH_MINUS))
			{
				if (this->m_Zoom > 1)
				{
					this->m_Zoom--;
				}
			}
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(3, 0));
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_SEARCH_PLUS))
			{
				if (this->m_Zoom < 3)
				{
					this->m_Zoom++;
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
