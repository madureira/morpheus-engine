#include "TextureXXX.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Morpheus {

	TextureXXX::TextureXXX(const char* filePath)
	{
		int x, y, n;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath, &x, &y, &n, STBI_rgb_alpha);

		if (!data)
		{
			std::cout << "ERROR" << std::endl;
			return;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	TextureXXX::~TextureXXX()
	{
		glDeleteTextures(1, &m_texture);
	}

	void TextureXXX::IncRefCount()
	{
		m_refCount++;
	}

	void TextureXXX::DecRefCount()
	{
		m_refCount--;
		if (m_refCount == 0)
		{
			delete this;
		}
	}

	GLuint TextureXXX::GetGLTexture()
	{
		return m_texture;
	}

}
