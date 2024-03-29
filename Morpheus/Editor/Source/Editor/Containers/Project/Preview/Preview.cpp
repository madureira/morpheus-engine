#include "Preview.h"
#include <Engine/Util/FileUtil.h>
#include "Editor/Widgets/Button/Button.h"

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
        , m_SceneIcon(new Morpheus::Texture("Assets/icons/cube-icon.png"))
        , m_Zoom(1)
    {
    }

    Preview::~Preview()
    {
        Shutdown();
        delete m_FolderIcon;
        delete m_FileIcon;
        delete m_SceneIcon;
    }

    void Preview::Render(entt::registry& registry)
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
            for (auto &item : m_Items)
            {
                ImGui::Dummy(ImVec2(margin, 0));
                ImGui::SameLine();

                ImGui::BeginGroup();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0, 0)));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0.25f, 0.25f, 0.25f, 1.00f)));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(150, 150, 150)));
                ImGui::PushID(itemId);
                if (ImGui::ImageButton((void*)item->image->GetID(), ImVec2((float)(imageSize * m_Zoom), (float)(imageSize * m_Zoom))))
                {
                    m_SelectedItem = item->data["path"].get<std::string>();
                }

                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
                {
                    if (item->data["type"].get<std::string>() == "folder")
                    {
                        m_HandleFolderSelection(m_SelectedItem);
                    }
                    else if (item->data["type"].get<std::string>() == "file")
                    {
                        m_HandleFileSelection(m_SelectedItem);
                    }
                }

                ImGui::PopID();
                ImGui::PopStyleColor(3);
                ImGui::Dummy(ImVec2(0, 5));
                ImGui::Dummy(ImVec2(5, 0));
                ImGui::SameLine();
                std::string truncatedText(TruncateFileName(item->title));
                ImVec2 textSize = ImGui::CalcTextSize(truncatedText.c_str());
                ImVec2 pos = ImGui::GetCursorPos();
                pos.x += (imageSize * m_Zoom - textSize.x) * 0.5f;
                ImGui::SetCursorPos(pos);
                ImGui::Text(truncatedText.c_str());
                ImGui::EndGroup();

                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::TextUnformatted(item->title.c_str());
                    ImGui::EndTooltip();
                }

                float nextSize = width + (margin * 3.0f) + (imageSize * m_Zoom);

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

            if (!m_CurrentFolder.empty())
            {
                auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
                auto& dropFilesComponent = registry.get<Morpheus::DropFilesComponent>(windowEntity.id);

                if (!dropFilesComponent.filesPath.empty())
                {
                    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
                    {
                        int copiedFiles = 0;
                        static std::string pathSep = Morpheus::FileUtil::PathSeparator();
                        for (auto& fileOrigin : dropFilesComponent.filesPath)
                        {
                            ME_LOG_WARN("Uploading file: {0}", fileOrigin);
                            std::string targetFile(m_CurrentFolder + pathSep + Morpheus::FileUtil::GetFileNameFromPath(fileOrigin));
                            Morpheus::FileUtil::CopyFile(fileOrigin, targetFile);
                            copiedFiles++;
                        }

                        if (copiedFiles == dropFilesComponent.filesPath.size())
                        {
                            auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
                            projectEntity.resetTreeViewOnly = true;
                            m_CurrentFolder = "";
                        }
                    }
                    dropFilesComponent.filesPath.clear();
                }
            }
        }
        ImGui::EndChild();

        if (!m_Items.empty())
        {
            DrawFooter(winSize.x);
        }
    }

    void Preview::UpdateSelectedFolder(std::string& folderPath)
    {
        if (m_CurrentFolder != folderPath)
        {
            m_SelectedItem = "";
            m_CurrentFolder = folderPath;
            m_JSON = Morpheus::JSON::parse(Morpheus::FileUtil::ReadDirectoryAsJsonString(m_CurrentFolder));

            Shutdown();

            for (auto node : m_JSON)
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
                        m_Items.push_back(
                            new PreviewItem(
                                currentNode["name"].get<std::string>(),
                                new Morpheus::Texture(currentNode["path"].get<std::string>().c_str()),
                                currentNode
                            )
                        );
                    }
                    else if (Morpheus::Extension::IsScene(currentNode["extension"]))
                    {
                        m_Items.push_back(
                            new PreviewItem(
                                currentNode["name"].get<std::string>(),
                                m_SceneIcon,
                                currentNode
                            )
                        );
                    }
                    else
                    {
                        m_Items.push_back(
                            new PreviewItem(
                                currentNode["name"].get<std::string>(),
                                m_FileIcon,
                                currentNode
                            )
                        );
                    }
                }
                else if (currentNode["type"] == "folder")
                {
                    m_Items.push_back(
                        new PreviewItem(
                            currentNode["name"].get<std::string>(),
                            m_FolderIcon,
                            currentNode
                        )
                    );
                }
            }

            std::sort(m_Items.begin(), m_Items.end(), [](const PreviewItem* a, const PreviewItem* b) {
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
        m_CurrentFile = filePath;
    }

    void Preview::Shutdown()
    {
        for (auto item : m_Items)
        {
            if (item->image != m_FileIcon && item->image != m_FolderIcon && item->image != m_SceneIcon)
            {
                delete item->image;
            }
            delete item;
        }
        m_Items.clear();
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
                ImGui::Text(m_SelectedItem.c_str());
            }
            ImGui::EndChild();

            ImGui::SameLine();
            ImGui::Dummy(ImVec2(4, 0));
            ImGui::SameLine();
            if (Button::Render(ICON_FA_SEARCH_MINUS))
            {
                if (m_Zoom > 1)
                {
                    m_Zoom--;
                }
            }
            ImGui::SameLine();
            ImGui::Dummy(ImVec2(3, 0));
            ImGui::SameLine();
            if (Button::Render(ICON_FA_SEARCH_PLUS))
            {
                if (m_Zoom < 3)
                {
                    m_Zoom++;
                }
            }
        }
        ImGui::EndChild();
    }

    std::string Preview::TruncateFileName(std::string fileName)
    {
        static const int SLOT_SIZE = 8;

        if (fileName.size() > SLOT_SIZE * m_Zoom)
        {
            return fileName.substr(0, SLOT_SIZE * m_Zoom) + "...";
        }

        return fileName;
    }

}
