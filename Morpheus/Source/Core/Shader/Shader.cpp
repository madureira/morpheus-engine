#include "Shader.h"

namespace Morpheus {

	Shader::Shader(const char* vertexPath, const char* fragmentPath) :
		m_VertPath(vertexPath),
		m_FragPath(fragmentPath)
	{
		this->m_ShaderID = this->Load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(this->m_ShaderID);
	}

	void Shader::Enable() const
	{
		glUseProgram(this->m_ShaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

	GLuint Shader::Load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = FileUtil::ReadFile(this->m_VertPath);
		std::string fragSourceString = FileUtil::ReadFile(this->m_FragPath);

		if (vertSourceString.empty())
		{
			std::cout << "Vertex shader is empty!" << std::endl;
			return 0;
		}

		if (fragSourceString.empty())
		{
			std::cout << "Fragment shader is empty!" << std::endl;
			return 0;
		}

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		GLint result;

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader! " << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!" << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLint Shader::GetUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(this->m_ShaderID, name);
	}

}
