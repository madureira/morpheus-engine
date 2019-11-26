#include "SpriteBatcher.h"

namespace Morpheus {

	SpriteBatcher::SpriteBatcher(glm::vec2 screenSize)
		: m_Shader(nullptr),
		m_Texture(nullptr)
	{
		this->m_Shader = new Morpheus::Shader("Assets/shaders/sprite.vert", "Assets/shaders/sprite.frag");

		// Get the texture uniform from the shader program.
		this->m_TextureUniform = glGetUniformLocation(this->m_Shader->GetProgram(), "tex");

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

		SetScreenSize(screenSize);
	}

	SpriteBatcher::~SpriteBatcher()
	{
		glDeleteProgram(this->m_Shader->GetProgram());
	}

	void SpriteBatcher::Draw(glm::vec4 destRect, glm::vec4 sourceRect, glm::vec4 color, Texture* pTexture)
	{
		// Draw doesn't actually have to draw anything.
		// Instead it collects a bunch of vertex information until flush is called, and then draws it all.

		// In one draw call we can only render sprites that have the same texture in.
		// If we get something with a different texture, we have to flush and start over.
		if (this->m_Texture != pTexture)
		{
			// Draw everything in the current buffer.
			this->Flush();

			// Make sure the texture exists so long as we are holding on to it.
			pTexture->IncRefCount();
			if (this->m_Texture != nullptr)
			{
				this->m_Texture->DecRefCount();
			}
			// Switch textures
			this->m_Texture = pTexture;
		}

		// Create vertices for the given draw request and add them to the buffer.
		// A more complex spritebatcher may allow for rotation of vertices, which would also happen here
		this->m_VertexBuffer.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y), glm::vec2(sourceRect.x, sourceRect.y), color));
		this->m_VertexBuffer.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
		this->m_VertexBuffer.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
		this->m_VertexBuffer.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y), glm::vec2(sourceRect.z, sourceRect.y), color));
		this->m_VertexBuffer.push_back(Vertex2dUVColor(glm::vec2(destRect.x, destRect.y + destRect.w), glm::vec2(sourceRect.x, sourceRect.w), color));
		this->m_VertexBuffer.push_back(Vertex2dUVColor(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w), glm::vec2(sourceRect.z, sourceRect.w), color));
	}

	void SpriteBatcher::Flush()
	{
		// If there's a false alarm, don't draw anything
		// (this will always happen on the first texture)
		if (this->m_VertexBuffer.size() == 0 || this->m_Texture == nullptr)
		{
			return;
		}

		// Set the current shader program.
		this->m_Shader->Enable();
		glBindVertexArray(this->m_VAO);

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->m_Texture->GetGLTexture());
		glUniform1i(this->m_TextureUniform, 0);

		// Copy our vertex buffer into the actual vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dUVColor) * this->m_VertexBuffer.size(), &this->m_VertexBuffer[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Set the screen transform matrix
		this->m_Shader->setMat3("screenTransform", this->m_ScreenTransform);
		this->m_Shader->setFloat("scale", this->m_Scale);

		// Enable vertex attributes for position, uv, and color
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Draw all indices in the index buffer
		glDrawArrays(GL_TRIANGLES, 0, this->m_VertexBuffer.size());

		// Disable vertex attribute
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindVertexArray(0);

		this->m_Shader->Disable();

		this->m_VertexBuffer.clear();
	}

	void SpriteBatcher::SetScreenSize(glm::vec2 screenSize)
	{
		// Since opengl normally renders with the screen being -1 to 1, and I want it from 0 to screen size,
		// I have to multiply everything by this scaling and translation matrix
		this->m_ScreenTransform[0][0] = 2 / screenSize.x;
		this->m_ScreenTransform[1][1] = 2 / screenSize.y;
		this->m_ScreenTransform[2][0] = -1;
		this->m_ScreenTransform[2][1] = -1;
	}

	void SpriteBatcher::SetScale(float scale)
	{
		this->m_Scale = scale;
	}

}

