#include "Texture.h"
#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Morpheus {

	Texture::Texture(std::string imagePath)
		: m_TextureID(0),
		m_ImagePath(imagePath),
		m_Width(0),
		m_Height(0),
		m_Channels(0)
	{
		glGenTextures(1, &this->m_TextureID);
		glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(imagePath.c_str(), &this->m_Width, &this->m_Height, &this->m_Channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_Width, this->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture: " << imagePath.c_str() << std::endl;
		}
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int Texture::GetID() const
	{
		return this->m_TextureID;
	}

	int Texture::GetWidth() const
	{
		return this->m_Width;
	}

	int Texture::GetHeight() const
	{
		return this->m_Height;
	}

}
