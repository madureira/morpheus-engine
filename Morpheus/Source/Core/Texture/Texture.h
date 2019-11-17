#pragma once

#include <string>

namespace Morpheus {

	class Texture
	{
	private:
		unsigned int m_TextureID;
		std::string m_ImagePath;
		int m_Width;
		int m_Height;
		int m_Channels;

	public:
		Texture(std::string imagePath);
		unsigned int GetID() const;
		int GetWidth() const;
		int GetHeight() const;
	};

}
