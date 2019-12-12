#pragma once

#include <string>
#include <fstream>

namespace Morpheus {

	class FileUtil
	{
	public:
		static std::string ReadFile(const char* filePath)
		{
			FILE* pFile;
			fopen_s(&pFile, filePath, "rt");

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
	};

}
