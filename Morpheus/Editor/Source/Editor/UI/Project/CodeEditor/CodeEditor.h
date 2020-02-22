#pragma once

#include "Editor/UI/UIComponent.h"
#include "Vendors/ImGuiColorTextEdit/TextEditor.h"
#include <string>

namespace Editor {

	class CodeEditor : public UIComponent
	{
	private:
		std::string m_FilePath;
		TextEditor* m_TextEditor;
		bool m_ShowEditor;

	public:
		CodeEditor(std::string filePath);
		~CodeEditor();

		void Draw(entt::registry& registry) override;
	};

}
