#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Morpheus {

	class TextureXXX
	{
	private:
		GLuint m_texture;
		unsigned int m_refCount = 0;

	public:
		TextureXXX(const char* filePath);
		~TextureXXX();
		void IncRefCount();
		void DecRefCount();
		GLuint GetGLTexture();

	};

}
