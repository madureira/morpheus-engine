#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture
{
private:
    GLuint m_texture;
    unsigned int m_refCount = 0;

public:
    Texture(const char* filePath);
    ~Texture();
    void IncRefCount();
    void DecRefCount();
    GLuint GetGLTexture();

};
