#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include "Core/Util/FileUtil.h"

namespace Morpheus {

	class Shader {
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		inline GLuint GetProgram() {
			return m_ShaderID;
		}

		void Enable() const;
		void Disable() const;

	private:
		GLuint Load();
		GLint GetUniformLocation(const GLchar* name);
	};

}
