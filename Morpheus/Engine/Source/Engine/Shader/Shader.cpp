#include "mepch.h"
#include "Shader.h"
#include <glad/glad.h>
#include <vector>
#include "Engine/Util/FileUtil.h"

namespace Morpheus {

	Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath)
		: m_VertPath(vertexPath)
		, m_FragPath(fragmentPath)
		, m_GeomPath(geometryPath)
	{
		this->m_ShaderID = this->Load();
	}

	Shader::~Shader()
	{
		if (this->m_ShaderID != 0)
		{
			glDeleteProgram(this->m_ShaderID);
		}
	}

	void Shader::Enable() const
	{
		glUseProgram(this->m_ShaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(this->GetUniformLocation(name.c_str()), (int)value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(this->GetUniformLocation(name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(this->GetUniformLocation(name.c_str()), value);
	}

	void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(this->GetUniformLocation(name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(this->m_ShaderID, name.c_str()), x, y);
	}

	void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(this->GetUniformLocation(name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(this->GetUniformLocation(name.c_str()), x, y, z);
	}

	void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(this->GetUniformLocation(name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(this->GetUniformLocation(name.c_str()), x, y, z, w);
	}

	void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	int Shader::GetUniformLocation(const std::string& name) const
	{
		return glGetUniformLocation(this->m_ShaderID, name.c_str());
	}

	unsigned int Shader::Load()
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

	bool Shader::CompileShader(unsigned int& program, int glShaderType, std::string shaderType, std::string shaderPath)
	{
		std::string shaderFile = FileUtil::ReadFile(shaderPath.c_str());

		if (shaderFile.empty())
		{
			ME_LOG_ERROR("Shader: {0} {1}", shaderType.c_str(), "shader is empty!");
			return false;
		}

		const char* shaderSource = shaderFile.c_str();

		GLuint shader = glCreateShader(glShaderType);

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		GLint isCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shader, length, &length, &error[0]);
			ME_LOG_ERROR("Shader: Failed to compile {0} {1} {2}", shaderType.c_str(), "shader! ", &error[0]);
			glDeleteShader(shader);
			return false;
		}

		glAttachShader(program, shader);

		return true;
	}

}
