#pragma once

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/Texture/Texture.h"
#include "Engine/Shader/Shader.h"
#include "Engine/ECS/ECS.h"

namespace Morpheus {

	constexpr auto MAX_LIGHT_SOURCES = 128;

	struct Vertex2dUVColor
	{
		glm::vec2 m_Position;
		glm::vec2 m_TexCoord;
		glm::vec4 m_Color;

		Vertex2dUVColor(glm::vec2 position, glm::vec2 texCoord, glm::vec4 color)
		{
			m_Position = position;
			m_TexCoord = texCoord;
			m_Color = color;
		}
	};

	struct SpotLight
	{
		glm::vec3 m_Position;
		glm::vec4 m_Color;
		glm::vec3 m_Falloff;

		SpotLight(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff)
		{
			m_Position = lightPosition;
			m_Color = lightColor;
			m_Falloff = lightFalloff;
		}
	};

	class SpriteRenderer
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		std::vector<Vertex2dUVColor> m_Vertices;
		std::vector<SpotLight> m_SpotLights;
		Shader* m_Shader;
		Shader* m_WireframeShader;
		Texture* m_DiffuseMap;
		Texture* m_NormalMap;
		Texture* m_SpecularMap;
		glm::mat3 m_ScreenTransform;
		glm::vec2 m_ScreenSize;
		glm::vec4 m_AmbientColor;
		float m_Scale;
		bool m_EnableNormal;
		bool m_EnableSpecular;
		bool m_EnableWireframe;
		int* m_DrawCalls;
		int* m_NumberOfVertices;

	public:
		SpriteRenderer(entt::registry& registry, glm::vec2 screenSize);
		~SpriteRenderer();

		void Draw(Texture* pDiffuseMap, Texture* pNormalMap, Texture* pSpecularMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color = glm::vec4(1, 1, 1, 1));
		void AddSpotLight(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff);
		void SetAmbientColor(glm::vec4 ambientColor);
		void SetScreenSize(glm::vec2 screenSize);
		void SetScale(float scale);
		void Render();
		void EnableNormal(bool enable = false);
		void EnableSpecular(bool enable = false);
		void EnableWireframe(bool enable = false);
	};

}

