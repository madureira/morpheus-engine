#pragma once

namespace Morpheus {

	class Texture
	{
	private:
		unsigned int m_Texture;

	public:
		Texture(const char* filePath, bool flipVertically = false);
		~Texture();
		unsigned int GetID();
	};

}
