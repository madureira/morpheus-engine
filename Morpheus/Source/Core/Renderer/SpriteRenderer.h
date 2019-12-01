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
		Vertex2dUVColor(glm::vec2 position, glm::vec2 texCoord, glm::vec4 color)
		{
			m_Position = position;
			m_TexCoord = texCoord;
			m_Color = color;
		}
	};

	struct Light
	{
		glm::vec3 m_Position;
		glm::vec4 m_Color;
		glm::vec3 m_Falloff;

		Light(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff)
		{
			m_Position = lightPosition;
			m_Color = lightColor;
			m_Falloff = lightFalloff;
		}
	};

	class SpriteRenderer
	{
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		std::vector<Vertex2dUVColor> m_Vertices;
		std::vector<Light> m_LightSources;
		Shader* m_Shader;
		Texture* m_DiffuseMap;
		Texture* m_NormalMap;
		glm::mat3 m_ScreenTransform;
		glm::vec2 m_ScreenSize;
		glm::vec4 m_AmbientColor;
		float m_Scale;

	public:
		SpriteRenderer(glm::vec2 screenSize);
		~SpriteRenderer();

		void Draw(Texture* pDiffuseMap, Texture* pNormalMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color = glm::vec4(1, 1, 1, 1));
		void AddLightSource(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff);
		void SetAmbientColor(glm::vec4 ambientColor);
		void Flush();

		// Call this to tell the spritebatcher how many pixels wide/tall the window is. Setting to 1 will make the entire screen render 1 pixel
		void SetScreenSize(glm::vec2 screenSize);
		void SetScale(float scale);
	};

}

