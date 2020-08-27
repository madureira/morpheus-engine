#pragma once

#include <string>
#include "Editor/Containers/UIContainer.h"
#include "Editor/Widgets/CodeEditor/CodeEditor.h"
#include "TreeView/TreeView.h"
#include "Preview/Preview.h"

namespace Editor {

    class Project final : public UIContainer
    {
    private:
        Preview* m_Preview;
        TreeView* m_TreeView;
        CodeEditor* m_CodeEditor;
        std::string m_ProjectPath;
        std::string m_CurrentSelectedFolder;
        std::string m_CurrentSelectedFile;

    public:
        Project(entt::registry& registry);
        ~Project();

        void Render(entt::registry& registry) override;

    private:
        void UpdateProjectPath(Morpheus::ProjectEntity& projectEntity);
        void OpenCodeEditor(entt::registry& registry);
    };

}
