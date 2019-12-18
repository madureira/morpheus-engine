#pragma once

namespace Morpheus {

	class Texture
	{
	private:
		unsigned int m_Texture;
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		Texture(const char* filePath, bool flipVertically = false);
		~Texture();
		unsigned int GetID();
		inline unsigned int GetWidth() { return m_Width; }
		inline unsigned int GetHeight() { return m_Height; }
	};

}
