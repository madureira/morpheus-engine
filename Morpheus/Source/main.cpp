#include "Core/Engine.h"
#include "Game/GameApp.h"


int main()
{
	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Start();

	return 0;
}


/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "shader.h"
#include "spriteBatcher.h"
#include <iostream>

SpriteBatcher* spriteBatcher;

// Window resize callback
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	spriteBatcher->SetScreenSize(glm::vec2(width, height));
}


int main(int argc, char** argv)
{
	// Initializes the GLFW library
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Initialize window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Sprite Batching!", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	//set resize callback
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}




	Texture* texture = new Texture("Assets/images/texture.png");
	texture->IncRefCount();

	// Create a spriteBatcher (This one will need the size of the screen)
	spriteBatcher = new SpriteBatcher(glm::vec2(800, 600));

	float frames = 0;
	float secCounter = 0;

	int tiles = 2048;
	int itemsPerLine = 32;
	int itemsPerColumn = 19;
	int spriteSize = 32;

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time and frame rate
		float dt = glfwGetTime();
		frames++;
		secCounter += dt;
		if (secCounter > 1.f)
		{
			std::string title = "FPS: " + std::to_string(frames);
			glfwSetWindowTitle(window, title.c_str());
			secCounter = 0;
			frames = 0;
		}
		glfwSetTime(0);



		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 0.0);

		int rowIndex = 0;
		int columnIndex = 0;
		int pass = 0;
		int passIndex = 0;

		for (int i = 0; i < tiles; i++) {
			if (columnIndex % itemsPerLine == 0 && i > 0) {
				rowIndex++;
				columnIndex = 0;
			}

			if (rowIndex % itemsPerColumn == 0 && i > 0) {
				rowIndex = 0;
			}

			if (passIndex == itemsPerLine * itemsPerColumn) {
				pass += 10;
				passIndex = 0;
			}

			spriteBatcher->Draw(

				// position of the rectangle
				glm::vec4(columnIndex * spriteSize + pass, rowIndex * spriteSize + pass, spriteSize, spriteSize),

				// rectangle size
				glm::vec4(0, 0, 300, 320),

				// color to tint the sprite
				glm::vec4(10.f, 10.f, 10.f, 0.1f),

				// texture of the sprite
				texture);

			columnIndex++;
			passIndex++;
		}




		// Now that we have a collection of all the draws we want to make, send it all to the gpu to be drawn!
		spriteBatcher->Flush();

		// Swap the backbuffer to the front.
		glfwSwapBuffers(window);

		// Poll input and window events.
		glfwPollEvents();

	}

	delete spriteBatcher;

	texture->DecRefCount();

	// Free GLFW memory.
	glfwTerminate();


	// End of Program.
	return 0;
}
*/
