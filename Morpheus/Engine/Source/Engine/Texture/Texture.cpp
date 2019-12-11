#include "mepch.h"
#include "Texture.h"
#include <glad/glad.h>
#include "Engine/Util/ImageLoader.h"

namespace Morpheus {

	Texture::Texture(const char* filePath, bool flipVertically)
		: m_Texture(0)
	{
		Image image = ImageLoader::Load(filePath, flipVertically);

		if (!image.pixels)
		{
			ME_CORE_ERROR("Texture: Fail to create the texture");
			return;
		}

		glGenTextures(1, &this->m_Texture);
		glBindTexture(GL_TEXTURE_2D, this->m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);

		ImageLoader::FreeImage(image);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->m_Texture);
	}

	unsigned int Texture::GetID()
	{
		return this->m_Texture;
	}

}
