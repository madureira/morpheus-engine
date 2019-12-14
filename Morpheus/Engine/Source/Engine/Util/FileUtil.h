#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace Morpheus {

	namespace fs = std::filesystem;

	class FileUtil
	{
	public:
		static std::string ReadFile(std::string filePath)
		{
			FILE* pFile;
			fopen_s(&pFile, filePath.c_str(), "rt");

			if (pFile == NULL)
			{
				ME_LOG_ERROR("FileUtil: Cannot open file: {0}", filePath);
				return "";
			}

			fseek(pFile, 0, SEEK_END);
			unsigned long length = ftell(pFile);
			unsigned long wideLength = length + 1;
			char* data = new char[wideLength];
			memset(data, 0, wideLength);
			fseek(pFile, 0, SEEK_SET);
			fread(data, 1, length, pFile);
			fclose(pFile);

			std::string result(data);
			delete[] data;

			return result;
		}

		static void WriteFile(std::string path, std::string fileName, std::string fileContent)
		{
			std::string filePathName(path + PathSeparator() + fileName);
			std::ofstream newFile(filePathName, std::ios_base::app);
			newFile << fileContent << "\n";
			newFile.close();
		}

		static bool CreateFolder(std::string path, std::string folderName)
		{
			std::string newDir(path + PathSeparator() + folderName);

			if (!fs::is_directory(newDir) || !fs::exists(newDir))
			{
				fs::create_directory(newDir);
				return true;
			}

			return false;
		}

		static std::string PathSeparator()
		{
#ifdef _WIN32
			return "\\";
#else
			return "/";
#endif
		}

	private:
		bool FileExists(const char* fileName)
		{
			if (FILE* file = fopen(fileName, "r")) {
				fclose(file);
				return true;
			}

			return false;
		}

	};

}
