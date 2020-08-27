#pragma once

namespace Morpheus {

    class Texture final
    {
    private:
        unsigned int m_Texture;
        unsigned int m_Width;
        unsigned int m_Height;

    public:
        Texture(const char* filePath, bool flipVertically = false);
        ~Texture();

        unsigned int GetID() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
    };

}
