#pragma once

#include <glad/glad.h>

namespace Morpheus {

	class Texture
	{
	private:
		GLuint m_Texture;

	public:
		Texture(const char* filePath, bool flipVertically = false);
		~Texture();
		GLuint GetID();
	};

}
