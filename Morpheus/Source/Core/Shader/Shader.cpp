#include "Shader.h"

#include <vector>
#include <iostream>
#include "Core/Util/FileUtil.h"

namespace Morpheus {

	Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath) :
		m_VertPath(vertexPath),
		m_FragPath(fragmentPath),
		m_GeomPath(geometryPath)
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

		this->CompileShader(program, GL_VERTEX_SHADER, "VERTEX", this->m_VertPath);
		this->CompileShader(program, GL_FRAGMENT_SHADER, "FRAGMENT", this->m_FragPath);

		if (!this->m_GeomPath.empty())
		{
			this->CompileShader(program, GL_GEOMETRY_SHADER, "GEOMETRY", this->m_GeomPath);
		}

		glLinkProgram(program);
		glValidateProgram(program);

		return program;
	}

	bool Shader::CompileShader(GLuint& program, int glShaderID, std::string shaderType, std::string shaderPath)
	{
		std::string shaderFile = FileUtil::ReadFile(shaderPath.c_str());

		if (shaderFile.empty())
		{
			std::cout << shaderType.c_str() << " shader is empty!" << std::endl;
			return false;
		}

		const char* shaderSource = shaderFile.c_str();

		GLint result;
		GLuint shader = glCreateShader(glShaderID);

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shader, length, &length, &error[0]);
			std::cout << "Failed to compile " << shaderType << " shader! " << &error[0] << std::endl;
			glDeleteShader(shader);
			return false;
		}

		glAttachShader(program, shader);

		return true;
	}

	GLint Shader::GetUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(this->m_ShaderID, name);
	}

}
