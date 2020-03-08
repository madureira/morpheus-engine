#pragma once

#include "Vendors/ImGuiColorTextEdit/TextEditor.h"
#include <string>

namespace Editor {

	class CodeEditor final
	{
	private:
		std::string m_FilePath;
		TextEditor* m_TextEditor;
		bool m_ShowEditor;

	public:
		CodeEditor(std::string filePath);
		~CodeEditor();

		void Draw();
	};

}
