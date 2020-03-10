#pragma once
#include <string>

namespace Editor {

	class FileSystemDialog final
	{
	public:
		static std::string OpenFolderSelector();
		static std::string OpenFileSelector(std::string filter = "");
		static std::string OpenSaveDialog();
	};

}
