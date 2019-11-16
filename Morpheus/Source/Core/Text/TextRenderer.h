#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Morpheus {

	class Shader;

	class TextRenderer
	{
	private:
		struct Character {
			GLuint TextureID;
			glm::ivec2 Size;
			glm::ivec2 Bearing;
			GLuint Advance;
		};
		std::map<GLchar, Character> m_Characters;
		GLuint m_VAO;
		GLuint m_VBO;

	public:
		TextRenderer(std::string fontPath);
		void Render(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	};

}
