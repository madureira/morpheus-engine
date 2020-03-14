#pragma once

#include <sstream>
#include <string>
#include <random>

namespace Morpheus {

	class UUID final
	{
	public:
		static std::string Generate(const unsigned int length = 6)
		{
			std::stringstream ss;
			for (int i = 0; i < length; i++)
			{
				const auto rc = RandomChar();
				std::stringstream hexstream;
				hexstream << std::hex << int(rc);
				auto hex = hexstream.str();
				ss << (hex.length() < 2 ? '0' + hex : hex);
			}
			return ss.str();
		}

	private:
		static unsigned char RandomChar()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 255);
			return static_cast<unsigned char>(dis(gen));
		}
	};

}
