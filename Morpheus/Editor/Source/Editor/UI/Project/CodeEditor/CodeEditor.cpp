#include "CodeEditor.h"
#include "Engine/Util/FileUtil.h"

namespace Editor {

	CodeEditor::CodeEditor(std::string filePath)
		: m_FilePath(filePath)
		, m_TextEditor(nullptr)
	{
		this->m_TextEditor = new TextEditor();

		std::string extension = filePath.substr(filePath.find_last_of(".") + 1);

		if (extension == "lua")
		{
			this->m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
		}
		else if (extension == "vert" || extension == "frag")
		{
			this->m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::GLSL());
		}
		else if (extension == "h" || extension == "cpp")
		{
			this->m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
		}

		this->m_TextEditor->SetText(Morpheus::FileUtil::ReadFile(this->m_FilePath));
	}

	CodeEditor::~CodeEditor()
	{
		delete this->m_TextEditor;
	}

	void CodeEditor::Draw(entt::registry& registry)
	{
		static bool showEditor = true;

		if (showEditor)
		{
			auto cpos = this->m_TextEditor->GetCursorPosition();

			ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
			ImGui::Begin(this->m_TextEditor->CanUndo() ? "Code Editor*" : "Code Editor", &showEditor, ImGuiWindowFlags_NoScrollbar);
			{
				ImVec2 codeEditorPos = ImGui::GetCursorPos();

				ImGui::BeginChild("textRender", ImVec2(0, codeEditorPos.y - 50));
				{
					this->m_TextEditor->Render("TextEditor");
				}
				ImGui::EndChild();
				
				ImGui::Text("Ln: %d, Col: %d | %s | %s | %s",
					cpos.mLine + 1,
					cpos.mColumn + 1,
					this->m_TextEditor->IsOverwrite() ? "Ovr" : "Ins",
					this->m_TextEditor->GetLanguageDefinition().mName.c_str(),
					this->m_FilePath.c_str());
			}

			ImGui::End();
		}
	}

}
