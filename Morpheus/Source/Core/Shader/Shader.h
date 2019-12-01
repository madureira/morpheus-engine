#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Morpheus {

	class Shader {
	private:
		GLuint m_ShaderID;
		std::string m_VertPath;
		std::string m_FragPath;
		std::string m_GeomPath;

	public:
		Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
		~Shader();

		inline GLuint GetProgram() {
			return m_ShaderID;
		}

		void Enable() const;
		void Disable() const;

		inline void SetBool(const std::string& name, bool value) const
		{
			glUniform1i(this->GetUniformLocation(name.c_str()), (int)value);
		}

		inline void SetInt(const std::string& name, int value) const
		{
			glUniform1i(this->GetUniformLocation(name.c_str()), value);
		}

		inline void SetFloat(const std::string& name, float value) const
		{
			glUniform1f(this->GetUniformLocation(name.c_str()), value);
		}

		inline void SetVec2(const std::string& name, const glm::vec2& value) const
		{
			glUniform2fv(this->GetUniformLocation(name.c_str()), 1, &value[0]);
		}

		inline void SetVec2(const std::string& name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(this->m_ShaderID, name.c_str()), x, y);
		}

		inline void SetVec3(const std::string& name, const glm::vec3& value) const
		{
			glUniform3fv(this->GetUniformLocation(name.c_str()), 1, &value[0]);
		}

		inline void SetVec3(const std::string& name, float x, float y, float z) const
		{
			glUniform3f(this->GetUniformLocation(name.c_str()), x, y, z);
		}

		inline void SetVec4(const std::string& name, const glm::vec4& value) const
		{
			glUniform4fv(this->GetUniformLocation(name.c_str()), 1, &value[0]);
		}

		inline void SetVec4(const std::string& name, float x, float y, float z, float w)
		{
			glUniform4f(this->GetUniformLocation(name.c_str()), x, y, z, w);
		}

		inline void SetMat2(const std::string& name, const glm::mat2& mat) const
		{
			glUniformMatrix2fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		inline void SetMat3(const std::string& name, const glm::mat3& mat) const
		{
			glUniformMatrix3fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		inline void SetMat4(const std::string& name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(this->GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}

		inline GLint GetUniformLocation(const std::string& name) const
		{
			return glGetUniformLocation(this->m_ShaderID, name.c_str());
		}

	private:
		GLuint Load();
		bool CompileShader(GLuint& program, int glShaderType, std::string shaderType, std::string shaderPath);
	};

}
