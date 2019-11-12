#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace Morpheus {

	class FileUtil
	{
	public:
		static std::string ReadFile(const char* filePath)
		{
			FILE* file;
			fopen_s(&file, filePath, "rt");

			if (file == NULL)
			{
				std::cout << "Cannot open file: " << filePath << std::endl;
				return "";
			}

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			unsigned long wideLength = length + 1;
			char* data = new char[wideLength];
			memset(data, 0, wideLength);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;

			return result;
		}
	};

}