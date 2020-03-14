#include "CodeEditor.h"
#include <Engine/Util/FileUtil.h>

namespace Editor {

	CodeEditor::CodeEditor(std::string filePath)
		: m_FilePath(filePath)
		, m_TextEditor(nullptr)
		, m_ShowEditor(false)
	{
		std::string extension = "." + filePath.substr(filePath.find_last_of(".") + 1);

		if (Morpheus::Extension::IsCode(extension) || Morpheus::Extension::IsData(extension) || Morpheus::Extension::IsShader(extension))
		{
			this->m_ShowEditor = true;
			this->m_TextEditor = new TextEditor();
			this->m_TextEditor->SetPalette(TextEditor::GetDarkPalette());

			if (Morpheus::Extension::IsShader(extension))
			{
				this->m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::GLSL());
			}
			else if (extension == Morpheus::Extension::LUA)
			{
				this->m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
			}
			else if (extension == Morpheus::Extension::H || extension == Morpheus::Extension::CPP)
			{
				this->m_TextEditor->SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
			}

			this->m_TextEditor->SetText(Morpheus::FileUtil::ReadFile(this->m_FilePath));
		}
	}

	CodeEditor::~CodeEditor()
	{
		this->m_FilePath.erase();
		delete this->m_TextEditor;
	}

	void CodeEditor::Draw()
	{
		if (this->m_ShowEditor)
		{
			auto cpos = this->m_TextEditor->GetCursorPosition();

			ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
			ImGui::Begin(this->m_TextEditor->CanUndo() ? "Code Editor*" : "Code Editor", &this->m_ShowEditor, ImGuiWindowFlags_NoScrollbar);
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
