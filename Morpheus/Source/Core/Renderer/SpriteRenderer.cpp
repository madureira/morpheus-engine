#include "SpriteRenderer.h"

namespace Morpheus {

	SpriteRenderer::SpriteRenderer(glm::vec2 screenSize)
		: m_Shader(nullptr),
		m_DiffuseMap(nullptr),
		m_NormalMap(nullptr),
		m_ScreenSize(screenSize)
	{
		this->m_Shader = new Morpheus::Shader("Assets/shaders/sprite.vert", "Assets/shaders/sprite.frag");

		// Setup vertex array
		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		// Setup vertex buffer
		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)sizeof(glm::vec2));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2dUVColor), (void*)sizeof(glm::vec4));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(0);

		this->m_AmbientColor = glm::vec4(1.0f, 1.0f, 1.f, 0.2f);

		this->m_Shader->Enable();

		glUniform1i(glGetUniformLocation(this->m_Shader->GetProgram(), "u_texture"), 0);
		glUniform1i(glGetUniformLocation(this->m_Shader->GetProgram(), "u_normals"), 1);

		this->m_Shader->setVec2("Resolution", this->m_ScreenSize);

		this->m_Shader->Disable();

		SetScreenSize(this->m_ScreenSize);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteProgram(this->m_Shader->GetProgram());
	}

	void SpriteRenderer::Draw(Texture* pDiffuseMap, Texture* pNormalMap, glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color)
	{
		// Draw doesn't actually have to draw anything.
		// Instead it collects a bunch of vertex information until flush is called, and then draws it all.

		// In one draw call we can only render sprites that have the same texture in.
		// If we get something with a different texture, we have to flush and start over.
		if (this->m_DiffuseMap != pDiffuseMap)
		{
			// Draw everything in the current buffer.
			this->Flush();

			// Make sure the texture exists so long as we are holding on to it.
			pDiffuseMap->IncRefCount();
			pNormalMap->IncRefCount();

			if (this->m_DiffuseMap != nullptr)
			{
				this->m_DiffuseMap->DecRefCount();
			}

			if (this->m_NormalMap != nullptr)
			{
				this->m_NormalMap->DecRefCount();
			}
			// Switch textures
			this->m_DiffuseMap = pDiffuseMap;
			this->m_NormalMap = pNormalMap;
		}

		// Create vertices for the given draw request and add them to the buffer.
		// A more complex spritebatcher may allow for rotation of vertices, which would also happen here
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y), glm::vec2(sourceRect.x, sourceRect.y), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
		this->m_Vertices.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w), glm::vec2(sourceRect.z, sourceRect.w), color));
	}

	void SpriteRenderer::AddLightSource(glm::vec3 lightPosition, glm::vec4 lightColor, glm::vec3 lightFalloff)
	{
		this->m_LightSources.push_back(Light(lightPosition, lightColor, lightFalloff));
	}

	void SpriteRenderer::SetAmbientColor(glm::vec4 ambientColor)
	{
		this->m_AmbientColor = ambientColor;
	}

	void SpriteRenderer::Flush()
	{
		if (this->m_Vertices.size() == 0 || this->m_DiffuseMap == nullptr)
		{
			return;
		}

		glm::vec3 lightPosition = this->m_LightSources[0].m_Position;

		lightPosition.x = lightPosition.x / this->m_ScreenSize.x;
		lightPosition.y = -((lightPosition.y - this->m_ScreenSize.y) / this->m_ScreenSize.y);
		lightPosition.z = lightPosition.z;

		this->m_Shader->Enable();

		this->m_Shader->setVec4("AmbientColor", this->m_AmbientColor);
		this->m_Shader->setVec3("LightPos", lightPosition);
		this->m_Shader->setVec4("LightColor", this->m_LightSources[0].m_Color);
		this->m_Shader->setVec3("LightFalloff", this->m_LightSources[0].m_Falloff);

		glBindVertexArray(this->m_VAO);

		// Bind normal
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->m_NormalMap->GetID());

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->m_DiffuseMap->GetID());

		// Copy our vertex buffer into the actual vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dUVColor) * this->m_Vertices.size(), &this->m_Vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Set the screen transform matrix
		this->m_Shader->setMat3("screenTransform", this->m_ScreenTransform);
		this->m_Shader->setFloat("scale", this->m_Scale);

		// Enable vertex attributes for position, uv, and color
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Draw all indices in the index buffer
		glDrawArrays(GL_TRIANGLES, 0, this->m_Vertices.size());

		// Disable vertex attribute
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);

		this->m_Shader->Disable();
		this->m_Vertices.clear();
		this->m_LightSources.clear();
	}

	void SpriteRenderer::SetScreenSize(glm::vec2 screenSize)
	{
		this->m_ScreenSize = screenSize;
		// Since opengl normally renders with the screen being -1 to 1, and I want it from 0 to screen size,
		// I have to multiply everything by this scaling and translation matrix
		this->m_ScreenTransform[0][0] = 2 / this->m_ScreenSize.x;
		this->m_ScreenTransform[1][1] = 2 / this->m_ScreenSize.y;
		this->m_ScreenTransform[2][0] = -1;
		this->m_ScreenTransform[2][1] = -1;

		this->m_Shader->Enable();
		this->m_Shader->setVec2("Resolution", this->m_ScreenSize);
		this->m_Shader->Disable();
	}

	void SpriteRenderer::SetScale(float scale)
	{
		this->m_Scale = scale;
	}

}

