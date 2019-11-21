#include "GameApp.h"


namespace Game {

	GameApp::~GameApp()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		//delete this->m_Shader;
	}

	void GameApp::Initialize(Morpheus::EventBus* pEventBus)
	{
		this->m_EventBus = pEventBus;

		texture = new Texture((char*)"Assets/images/tileset.png");
		texture->IncRefCount();

		spriteBatcher = new SpriteBatcher(glm::vec2(800, 600));

		/*
		this->m_Shader = new Morpheus::ShaderXXX("Assets/shaders/texture.vert", "Assets/shaders/texture.frag");

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		this->m_Texture = new Morpheus::TextureXXX("Assets/images/wall.jpg");


		this->m_Shader->Enable();
		glUniform1i(glGetUniformLocation(this->m_Shader->GetProgram(), "texture1"), 0);
		this->m_Shader->Disable();
		*/
	}

	void GameApp::OnFrameStarted(double deltaTime, int frame)
	{
		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->m_Texture->GetGLTexture());

		this->m_Shader->Enable();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		this->m_Shader->Disable();
		*/

		
		int columns = 19;
		int rows = 14;
		int layers = 5;
		int distance = -10;
		int margin = 40;
		int tileSize = 40;

		


		for (int x = 0; x < columns; x++)
		{
			for (int y = 0; y < rows; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					spriteBatcher->Draw(

						// position of the rectangle
						glm::vec4(margin + x * tileSize + z * distance, margin + y * tileSize + z * distance, tileSize, tileSize),

						// rectangle size
						//          
						//glm::vec4(32, 32, 64, 0),
						getTile(tileSize, z),

						// color to tint the sprite
						glm::vec4(x / 10.f, y / 10.f, z / 10.f, 1),

						// texture of the sprite
						texture);

					// Uncomment this line to see how much slower it is to call draw separately for each sprite.
					//spriteBatcher->Flush();
				}
			}
		}

		spriteBatcher->Flush();
	}

	void GameApp::FrameListener(double deltaTime, int frame)
	{
	}

	glm::vec4 GameApp::getTile(int tileSize, int layer)
	{
		if (layer == 0)
		{
			return glm::vec4(0, tileSize, tileSize, 0);
		}

		if (layer == 1)
		{
			return glm::vec4(tileSize * 8, tileSize, tileSize * 9, 0);
		}

		if (layer == 2)
		{
			return glm::vec4(tileSize * 4, tileSize, tileSize * 5, 0);
		}

		if (layer == 3)
		{
			return glm::vec4(tileSize * 4, tileSize * 4, tileSize * 5, tileSize * 3);
		}

		if (layer == 4)
		{
			return glm::vec4(tileSize, tileSize, tileSize * 2, 0);
		}
	}

}
