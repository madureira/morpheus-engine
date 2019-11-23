#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Texture/Texture.h"
#include "Core/Shader/Shader.h"

namespace Morpheus {

	struct Vertex2dUVColor
	{
		glm::vec2 m_Position;
		glm::vec2 m_TexCoord;
		glm::vec4 m_Color;

		// Makes a 2d vertex with uc and color data.
		Vertex2dUVColor() {}
		Vertex2dUVColor(glm::vec2 position, glm::vec2 texCoord, glm::vec4 color)
		{
			m_Position = position;
			m_TexCoord = texCoord;
			m_Color = color;
		}
	};

	class SpriteBatcher
	{
	private:
		GLuint m_VBO;
		std::vector<Vertex2dUVColor> m_VertexBuffer;
		Shader* m_Shader;
		Texture* m_Texture;
		GLuint m_TextureUniform;
		glm::mat3 m_ScreenTransform;
		GLuint m_ScreenTransformUniform;

	public:
		SpriteBatcher(glm::vec2 screenSize);
		~SpriteBatcher();

		void Draw(glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color, Texture* pTexture);
		void Flush();

		// Call this to tell the spritebatcher how many pixels wide/tall the window is. Setting to 1 will make the entire screen render 1 pixel
		void SetScreenSize(glm::vec2 screenSize);
	};

}

