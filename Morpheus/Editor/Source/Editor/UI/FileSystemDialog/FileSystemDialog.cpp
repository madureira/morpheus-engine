#include "FileSystemDialog.h"
#include "Engine/Log/Log.h"
#include <nfd.h>

namespace Editor {

	std::string FileSystemDialog::OpenFolderSelector()
	{
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_PickFolder(NULL, &outPath);

		std::string selectedPath;

		if (result == NFD_OKAY) {
			selectedPath = outPath;
			free(outPath);
		}
		else if (result == NFD_ERROR) {
			ME_LOG_ERROR("FileSystemDialog: {0}", NFD_GetError());
		}

		return selectedPath;
	}

	std::string FileSystemDialog::OpenFileSelector()
	{
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

		std::string selectedPath;

		if (result == NFD_OKAY) {
			selectedPath = outPath;
			free(outPath);
		}
		else if (result == NFD_ERROR) {
			ME_LOG_ERROR("FileSystemDialog: {0}", NFD_GetError());
		}

		return selectedPath;
	}

	std::string FileSystemDialog::OpenSaveDialog()
	{
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_SaveDialog(NULL, NULL, &outPath);

		std::string selectedPath;

		if (result == NFD_OKAY) {
			selectedPath = outPath;
			free(outPath);
		}
		else if (result == NFD_ERROR) {
			ME_LOG_ERROR("FileSystemDialog: {0}", NFD_GetError());
		}

		return selectedPath;
	}

}
