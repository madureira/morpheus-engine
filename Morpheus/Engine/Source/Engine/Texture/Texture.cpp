#include "mepch.h"
#include "Texture.h"
#include <glad/glad.h>
#include "Engine/Util/ImageLoader.h"

namespace Morpheus {

    Texture::Texture(const char* filePath, bool flipVertically)
        : m_Texture(0)
        , m_Width(0)
        , m_Height(0)
    {
        Image image;

        ImageLoader::Load(filePath, flipVertically, image);

        if (!image.pixels)
        {
            ME_LOG_ERROR("Texture: Fail to create the texture");
            return;
        }

        m_Width = image.width;
        m_Height = image.height;

        glGenTextures(1, &m_Texture);
        glBindTexture(GL_TEXTURE_2D, m_Texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        ImageLoader::FreeImage(image);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_Texture);
    }

    unsigned int Texture::GetID() const
    {
        return m_Texture;
    }

    unsigned int Texture::GetWidth() const
    {
        return m_Width;
    }

    unsigned int Texture::GetHeight() const
    {
        return m_Height;
    }

}
