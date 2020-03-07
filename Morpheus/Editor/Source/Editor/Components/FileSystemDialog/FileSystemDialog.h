#pragma once
#include <string>

namespace Editor {

	class FileSystemDialog
	{
	public:
		static std::string OpenFolderSelector();
		static std::string OpenFileSelector();
		static std::string OpenSaveDialog();
	};

}
