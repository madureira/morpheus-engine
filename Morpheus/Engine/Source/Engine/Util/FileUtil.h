#pragma once

#include <Engine/Log/Log.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <Engine/Util/JSON.h>
#include <iostream>

namespace Morpheus {

	namespace fs = std::filesystem;

	struct Extension final
	{
		inline static const std::string PNG = ".png";
		inline static const std::string JPG = ".jpg";
		inline static const std::string JPEG = ".jpeg";
		inline static const std::string GIF = ".gif";
		inline static const std::string ICO = ".ico";
		inline static const std::string H = ".h";
		inline static const std::string C = ".c";
		inline static const std::string CPP = ".cpp";
		inline static const std::string LUA = ".lua";
		inline static const std::string JSON = ".json";
		inline static const std::string XML = ".xml";
		inline static const std::string TTF = ".ttf";
		inline static const std::string VERT = ".vert";
		inline static const std::string FRAG = ".frag";
		inline static const std::string GEOM = ".geom";
		inline static const std::string SCN = ".scn";

		bool static IsImage(std::string extension)
		{
			return (extension == PNG || extension == JPG || extension == JPEG || extension == GIF);
		}

		bool static IsCode(std::string extension)
		{
			return (extension == H || extension == C || extension == CPP || extension == LUA);
		}

		bool static IsData(std::string extension)
		{
			return (extension == JSON || extension == XML);
		}

		bool static IsFont(std::string extension)
		{
			return (extension == TTF);
		}

		bool static IsShader(std::string extension)
		{
			return (extension == VERT || extension == FRAG || extension == GEOM);
		}

		bool static IsScene(std::string extension)
		{
			return (extension == SCN);
		}
	};

	class FileUtil final
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
			std::ofstream newFile(filePathName, std::ios_base::trunc);
			newFile << fileContent << "\n";
			newFile.close();
		}

		static bool CreateFolder(std::string path, std::string folderName)
		{
			std::string newDir(path + PathSeparator() + folderName);

			if (!fs::exists(newDir) || !fs::is_directory(newDir))
			{
				fs::create_directory(newDir);
				return true;
			}

			return false;
		}

		static std::string ReadDirectoryTreeAsJsonString(std::string& path)
		{
			Morpheus::JSON tree;
			BuildDirectoryTree(path, tree);
			return tree.dump();
		}

		static std::string ReadDirectoryAsJsonString(std::string& path)
		{
			Morpheus::JSON items = Morpheus::JSON::array();
			for (const auto& entry : fs::directory_iterator(path))
			{
				Morpheus::JSON node = Morpheus::JSON::object();
				node["name"] = entry.path().filename().string();
				node["path"] = entry.path().string();

				if (entry.is_directory())
				{
					node["type"] = "folder";
				}
				else if (entry.is_regular_file())
				{
					node["type"] = "file";
					node["extension"] = std::filesystem::path(entry).extension().string();
					node["size"] = std::to_string(entry.file_size()) + " bytes";

				}
				items.push_back(node);
			}

			return items.dump();
		}

		static void CopyFile(std::string& origin, std::string& target)
		{
			fs::copy(origin, target, fs::copy_options::overwrite_existing);
		}

		static std::string GetFileNameFromPath(std::string& filePath)
		{
			return fs::path(filePath).filename().string();
		}

		static bool IsFile(std::string& filePath)
		{
			return fs::is_regular_file(filePath);
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
		bool FileExists(std::string& path)
		{
			return fs::exists(path);
		}

		void static BuildDirectoryTree(const fs::path& pathToScan, Morpheus::JSON& tree)
		{
			for (const auto& entry : fs::directory_iterator(pathToScan))
			{
				if (tree.is_null())
				{
					tree["name"] = entry.path().parent_path().filename().string();
					tree["path"] = entry.path().parent_path().string();
					tree["type"] = "folder";
					tree["children"] = Morpheus::JSON::array();
				}

				Morpheus::JSON node = Morpheus::JSON::object();
				node["name"] = entry.path().filename().string();
				node["path"] = entry.path().string();

				if (entry.is_directory())
				{
					node["type"] = "folder";
					node["children"] = Morpheus::JSON::array();

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
