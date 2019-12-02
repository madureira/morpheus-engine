#include "mepch.h"
#include "SpriteRenderer.h"

namespace Morpheus {

	SpriteRenderer::SpriteRenderer(glm::vec2 screenSize)
		: m_Shader(nullptr),
		m_DiffuseMap(nullptr),
		m_NormalMap(nullptr),
		m_ScreenSize(screenSize),
		m_AmbientColor(glm::vec4(1.0f, 1.0f, 1.f, 0.25f))
	{
		this->m_Shader = new Morpheus::Shader("Assets/shaders/sprite.vert", "Assets/shaders/sprite.frag");

		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)sizeof(glm::vec2));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)sizeof(glm::vec4));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(0);

		this->m_Shader->Enable();
		this->m_Shader->SetVec2("Resolution", this->m_ScreenSize);
		glUniform1i(this->m_Shader->GetUniformLocation("u_texture"), 0);
		glUniform1i(this->m_Shader->GetUniformLocation("u_normals"), 1);
		this->m_Shader->Disable();

		SetScreenSize(this->m_ScreenSize);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteProgram(this->m_Shader->GetProgram());
	}

	void SpriteRenderer::Draw(Texture* pDiffuseMap, Texture* pNormalMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color)
	{
		if (this->m_DiffuseMap != pDiffuseMap)
		{
			this->Render();
			this->m_DiffuseMap = pDiffuseMap;
			this->m_NormalMap = pNormalMap;
		}

		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y), glm::vec2(sourceRect.x, sourceRect.y), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w), glm::vec2(sourceRect.z, sourceRect.w), color));
	}

	void SpriteRenderer::AddLightSource(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff)
	{
		if (this->m_LightSources.size() < MAX_LIGHT_SOURCES)
		{
			this->m_LightSources.push_back(LightSource(lightPosition, lightColor, lightFalloff));
		}
	}

	void SpriteRenderer::SetAmbientColor(glm::vec4 ambientColor)
	{
		this->m_AmbientColor = ambientColor;
	}

	void SpriteRenderer::SetScreenSize(glm::vec2 screenSize)
	{
		this->m_ScreenSize = screenSize;

		this->m_ScreenTransform[0][0] = 2 / this->m_ScreenSize.x;
		this->m_ScreenTransform[1][1] = 2 / this->m_ScreenSize.y;
		this->m_ScreenTransform[2][0] = -1;
		this->m_ScreenTransform[2][1] = -1;

		this->m_Shader->Enable();
		this->m_Shader->SetVec2("Resolution", this->m_ScreenSize);
		this->m_Shader->Disable();
	}

	void SpriteRenderer::SetScale(float scale)
	{
		this->m_Scale = scale;
	}

	void SpriteRenderer::Render()
	{
		if (this->m_Vertices.size() == 0 || this->m_DiffuseMap == nullptr)
		{
			return;
		}

		this->m_Shader->Enable();

		this->m_Shader->SetVec4("AmbientColor", this->m_AmbientColor);
		this->m_Shader->SetMat3("screenTransform", this->m_ScreenTransform);
		this->m_Shader->SetFloat("scale", this->m_Scale);

		glm::vec3 lightPositions[MAX_LIGHT_SOURCES] = { };
		glm::vec4 lightColors[MAX_LIGHT_SOURCES] = { };
		glm::vec3 lightFalloffs[MAX_LIGHT_SOURCES] = { };

		int index = 0;
		for (auto light : this->m_LightSources)
		{
			glm::vec3 lightPosition = light.m_Position;

			lightPosition.x = lightPosition.x / this->m_ScreenSize.x;
			lightPosition.y = -((lightPosition.y - this->m_ScreenSize.y) / this->m_ScreenSize.y);
			lightPosition.z = lightPosition.z;

			lightPositions[index] = lightPosition;
			lightColors[index] = light.m_Color;
			lightFalloffs[index] = light.m_Falloff;

			index++;
		}

		this->m_Shader->SetInt("TotalLightSources", (GLsizei) this->m_LightSources.size());
		glUniform3fv(this->m_Shader->GetUniformLocation("LightPos"), (GLsizei) this->m_LightSources.size(), (float*) lightPositions);
		glUniform4fv(this->m_Shader->GetUniformLocation("LightColor"), (GLsizei) this->m_LightSources.size(), (float*) lightColors);
		glUniform3fv(this->m_Shader->GetUniformLocation("LightFalloff"), (GLsizei) this->m_LightSources.size(), (float*) lightFalloffs);

		glBindVertexArray(this->m_VAO);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->m_NormalMap->GetID());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->m_DiffuseMap->GetID());

		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dUVColor) * this->m_Vertices.size(), &this->m_Vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Enable vertex attributes for position, uv, and color
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawArrays(GL_TRIANGLES, 0, (GLsizei) this->m_Vertices.size());

		// Disable vertex attribute
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);

		this->m_Shader->Disable();
		this->m_Vertices.clear();
		this->m_LightSources.clear();
	}

}

