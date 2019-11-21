/*
Title: Sprite Batching
File Name: spriteBatcher.h
Copyright ? 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "texture.h"

struct Vertex2dUVColor
{

    glm::vec2 m_position;
    glm::vec2 m_texCoord;
    glm::vec4 m_color;

    // Makes a 2d vertex with uc and color data.
	Vertex2dUVColor() {}
    Vertex2dUVColor(glm::vec2 position, glm::vec2 texCoord, glm::vec4 color)
    {
        m_position = position;
        m_texCoord = texCoord;
        m_color = color;
    }
};



class SpriteBatcher
{

public:
    SpriteBatcher(glm::vec2 screenSize);
    ~SpriteBatcher();

    void Draw(glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color, Texture* texture);
    void Flush();

    // Call this to tell the spritebatcher how many pixels wide/tall the window is. Setting to 1 will make the entire screen render 1 pixel
    void SetScreenSize(glm::vec2 screenSize);

private:

    // Collection of vertices
    std::vector<Vertex2dUVColor> m_vertexBuffer;
    GLuint m_vbo;

    // Shaders.
    Shader m_vertexShader;
    Shader m_fragmentShader;

    // GL index for the shader program
    GLuint m_shaderProgram;

    // Texture and uniform location
    Texture* m_texture;
    GLuint m_textureUniform;

    // stuff to send word matrices
    glm::mat3 m_screenTransform;
    GLuint m_screenTransformUniform;
};
