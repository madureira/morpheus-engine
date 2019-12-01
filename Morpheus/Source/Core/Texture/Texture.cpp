#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Morpheus {

	Texture::Texture(const char* filePath, bool flipVertically)
		: m_Texture(0)
	{
		int x, y, n;

		stbi_set_flip_vertically_on_load(flipVertically);
		unsigned char* data = stbi_load(filePath, &x, &y, &n, STBI_rgb_alpha);

		if (!data)
		{
			std::cout << "ERROR: Fail to load the texture: " << filePath << std::endl;
			return;
		}

		glGenTextures(1, &this->m_Texture);
		glBindTexture(GL_TEXTURE_2D, this->m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->m_Texture);
	}

	void Texture::IncRefCount()
	{
		this->m_RefCount++;
	}

	void Texture::DecRefCount()
	{
		this->m_RefCount--;
		if (this->m_RefCount == 0)
		{
			delete this;
		}
	}

	GLuint Texture::GetID()
	{
		return this->m_Texture;
	}

}
