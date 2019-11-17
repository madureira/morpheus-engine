#pragma once

#include <string>
#include <glad/glad.h>

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

	private:
		GLuint Load();
		bool CompileShader(GLuint& program, int glShaderID, std::string shaderType, std::string shaderPath);
		GLint GetUniformLocation(const GLchar* name);
	};

}
