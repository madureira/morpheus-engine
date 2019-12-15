#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace Morpheus {

	namespace fs = std::filesystem;
	using json = nlohmann::json;

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

		static std::string ReadDirectoryTreeAsJsonString(std::string& path)
		{
			json tree;
			BuildDirectoryTree(path, tree);
			return tree.dump();
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

		void static BuildDirectoryTree(const fs::path& pathToScan, json& tree)
		{
			for (const auto& entry : fs::directory_iterator(pathToScan)) {
				if (tree.is_null())
				{
					tree["name"] = entry.path().parent_path().filename().string();
					tree["path"] = entry.path().parent_path().string();
					tree["type"] = "folder";
					tree["children"] = json::array();
				}

				json node = json::object();
				node["name"] = entry.path().filename().string();
				node["path"] = entry.path().string();

				if (entry.is_directory())
				{
					node["type"] = "folder";
					node["children"] = json::array();

					if (tree.is_null())
					{
						tree = node;
						BuildDirectoryTree(entry, tree);
					}
					else
					{
						tree["children"].push_back(node);
						BuildDirectoryTree(entry, tree["children"].back());
					}
				}
				else if (entry.is_regular_file())
				{
					node["type"] = "file";
					node["extension"] = std::filesystem::path(entry).extension().string();
					node["size"] = std::to_string(entry.file_size()) + " bytes";

					tree["children"].push_back(node);
				}
			}
		}

	};

}
