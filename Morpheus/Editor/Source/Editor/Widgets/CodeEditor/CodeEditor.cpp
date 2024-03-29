#include "CodeEditor.h"
#include <Engine/Util/FileUtil.h>
#include "Vendors/IconsFontAwesome5/IconsFontAwesome5.h"

namespace Editor {

    CodeEditor::CodeEditor(std::string filePath)
        : m_FilePath(filePath)
        , m_TextEditor(nullptr)
        , m_ShowEditor(false)
    {
        std::string extension = "." + filePath.substr(filePath.find_last_of(".") + 1);

        if (Morpheus::Extension::IsCode(extension) || Morpheus::Extension::IsData(extension) || Morpheus::Extension::IsShader(extension))
        {
            m_ShowEditor = true;
            m_TextEditor = new TextEditor();
            m_TextEditor->SetPalette(TextEditor::GetDarkPalette());

            if (Morpheus::Extension::IsShader(extension))
            {
                m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::GLSL());
            }
            else if (extension == Morpheus::Extension::LUA)
            {
                m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
            }
            else if (extension == Morpheus::Extension::H || extension == Morpheus::Extension::CPP)
            {
                m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
            }

            m_TextEditor->SetText(Morpheus::FileUtil::ReadFile(m_FilePath));
        }
    }

    CodeEditor::~CodeEditor()
    {
        m_FilePath.erase();
        delete m_TextEditor;
    }

    void CodeEditor::Draw()
    {
        if (m_ShowEditor)
        {
            auto cpos = m_TextEditor->GetCursorPosition();

            static ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
            ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
            std::string title(ICON_FA_CODE);
            title += "  ";
            title += m_TextEditor->CanUndo() ? "Code Editor*" : "Code Editor";

            ImGui::Begin(title.c_str(), &m_ShowEditor, flags);
            {
                ImVec2 codeEditorPos = ImGui::GetCursorPos();

                ImGui::BeginChild("textRender", ImVec2(0, codeEditorPos.y - 50));
                {
                    m_TextEditor->Render("TextEditor");
                }
                ImGui::EndChild();

                ImGui::Text("Ln: %d, Col: %d | %s | %s | %s",
                    cpos.mLine + 1,
                    cpos.mColumn + 1,
                    m_TextEditor->IsOverwrite() ? "Ovr" : "Ins",
                    m_TextEditor->GetLanguageDefinition().mName.c_str(),
                    m_FilePath.c_str());
            }
            ImGui::End();
        }
    }

}
