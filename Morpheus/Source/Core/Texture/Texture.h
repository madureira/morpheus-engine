#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Morpheus {

	class Texture
	{
	private:
		GLuint m_Texture;
		unsigned int m_RefCount = 0;

	public:
		Texture(const char* filePath, bool flipVertically = false);
		~Texture();
		void IncRefCount();
		void DecRefCount();
		GLuint GetGLTexture();
	};

}
