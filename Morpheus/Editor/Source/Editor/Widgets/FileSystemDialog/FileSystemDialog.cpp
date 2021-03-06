#include "FileSystemDialog.h"
#include <nfd.h>
#include <Engine/Log/Log.h>

namespace Editor {

    std::string FileSystemDialog::OpenFolderSelector()
    {
        nfdchar_t* outPath = NULL;
        nfdresult_t result = NFD_PickFolder(NULL, &outPath);

        std::string selectedPath;

        if (result == NFD_OKAY)
        {
            selectedPath = outPath;
            free(outPath);
        }
        else if (result == NFD_ERROR)
        {
            ME_LOG_ERROR("FileSystemDialog: {0}", NFD_GetError());
        }

        return selectedPath;
    }

    std::string FileSystemDialog::OpenFileSelector(std::string filter)
    {
        nfdchar_t* outPath = NULL;
        nfdresult_t result = NFD_OpenDialog((filter.empty() ? NULL : filter.c_str()), NULL, &outPath);

        std::string selectedPath;

        if (result == NFD_OKAY)
        {
            selectedPath = outPath;
            free(outPath);
        }
        else if (result == NFD_ERROR)
        {
            ME_LOG_ERROR("FileSystemDialog: {0}", NFD_GetError());
        }

        return selectedPath;
    }

    std::string FileSystemDialog::OpenSaveDialog()
    {
        nfdchar_t* outPath = NULL;
        nfdresult_t result = NFD_SaveDialog(NULL, NULL, &outPath);

        std::string selectedPath;

        if (result == NFD_OKAY)
        {
            selectedPath = outPath;
            free(outPath);
        }
        else if (result == NFD_ERROR)
        {
            ME_LOG_ERROR("FileSystemDialog: {0}", NFD_GetError());
        }

        return selectedPath;
    }

}
