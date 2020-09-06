#include "Project.h"
#include <functional>
#include <Engine/Util/FileUtil.h>
#include "Editor/Widgets/CodeEditor/CodeEditor.h"
#include "TreeView/TreeView.h"
#include "Preview/Preview.h"

namespace Editor {

    Project::Project(entt::registry& registry)
        : m_Preview(nullptr)
        , m_TreeView(nullptr)
        , m_CodeEditor(nullptr)
        , m_ProjectPath("")
        , m_CurrentSelectedFolder("")
        , m_CurrentSelectedFile("")
    {
        this->m_Preview = new Preview(
            [&selectedFolder = this->m_CurrentSelectedFolder](std::string selectedFolderByUser) {
                selectedFolder = selectedFolderByUser;
            },
            [&selectedFile = this->m_CurrentSelectedFile](std::string selectedFileByUser) {
                selectedFile = selectedFileByUser;
            }
        );
    }

    Project::~Project()
    {
        delete this->m_Preview;
        delete this->m_TreeView;
        delete this->m_CodeEditor;
    }

    void Project::Render(entt::registry& registry)
    {
        auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

        this->UpdateProjectPath(projectEntity);
        this->OpenCodeEditor(registry);

        static bool* show = NULL;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

        ImGui::Begin(ICON_FA_FOLDER"  Project###project", show, windowFlags);
        {
            static float s_treeViewWidth = 200.0f;
            ImVec2 contentRegionMax = ImGui::GetWindowContentRegionMax();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.180f, 0.180f , 0.180f , 1.00f });
            ImGui::BeginChild("TreeView", ImVec2(s_treeViewWidth, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
            {
                if (this->m_TreeView != nullptr)
                {
                    this->m_TreeView->Render(registry);
                }
            }
            ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::SameLine();

            ImGui::Button("vsplitter", ImVec2(5.0f, contentRegionMax.y - 28));
            if (ImGui::IsItemHovered())
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
            }

            if (ImGui::IsItemActive())
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
                if (s_treeViewWidth + ImGui::GetIO().MouseDelta.x > 10 && s_treeViewWidth + ImGui::GetIO().MouseDelta.x < contentRegionMax.x - 20)
                {
                    s_treeViewWidth += ImGui::GetIO().MouseDelta.x;
                }
            }
            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.180f, 0.180f , 0.180f , 1.00f });
            ImGui::BeginChild("FilesPreview", ImVec2(0, 0), false);
            {
                this->m_Preview->UpdateSelectedFolder(this->m_CurrentSelectedFolder);
                this->m_Preview->Render(registry);
            }
            ImGui::EndChild();
            ImGui::PopStyleColor();

            ImGui::PopStyleVar();
        }
        ImGui::End();
    }

    void Project::UpdateProjectPath(Morpheus::ProjectEntity& projectEntity)
    {
        if (projectEntity.resetTreeViewOnly)
        {
            projectEntity.resetTreeViewOnly = false;
            delete this->m_TreeView;
            this->m_TreeView = new TreeView(this->m_ProjectPath,
                [&selectedFolder = this->m_CurrentSelectedFolder](std::string selectedFolderByUser) {
                    selectedFolder = selectedFolderByUser;
                },
                [&selectedFile = this->m_CurrentSelectedFile](std::string selectedFileByUser) {
                    selectedFile = selectedFileByUser;
                }
            );
        }
        else if (projectEntity.reload || (this->m_ProjectPath != projectEntity.path && !projectEntity.path.empty()))
        {
            projectEntity.reload = false;
            this->m_CurrentSelectedFolder = this->m_ProjectPath;
            this->m_ProjectPath = projectEntity.path;
            this->m_CurrentSelectedFile = "";

            delete this->m_TreeView;
            this->m_TreeView = new TreeView(this->m_ProjectPath,
                [&selectedFolder = this->m_CurrentSelectedFolder](std::string selectedFolderByUser) {
                    selectedFolder = selectedFolderByUser;
                },
                [&selectedFile = this->m_CurrentSelectedFile](std::string selectedFileByUser) {
                    selectedFile = selectedFileByUser;
                }
            );
        }
    }

    void Project::OpenCodeEditor(entt::registry& registry)
    {
        static bool showCodeEditor = false;
        static std::string filePath = "";

        if (!this->m_CurrentSelectedFile.empty() && this->m_CurrentSelectedFile != filePath)
        {
            showCodeEditor = true;
            filePath = this->m_CurrentSelectedFile;
            this->m_CodeEditor = new CodeEditor(this->m_CurrentSelectedFile);
        }

        if (showCodeEditor)
        {
            this->m_CodeEditor->Draw();
        }
    }

}
