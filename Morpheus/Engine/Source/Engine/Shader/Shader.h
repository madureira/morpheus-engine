#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Morpheus {

	class Shader {
	private:
		unsigned int m_ShaderID;
		std::string m_VertPath;
		std::string m_FragPath;
		std::string m_GeomPath;

	public:
		Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
		~Shader();

		inline unsigned int GetProgram() { return m_ShaderID; }

		void Enable() const;
		void Disable() const;

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec2(const std::string& name, const glm::vec2& value) const;
		void SetVec2(const std::string& name, float x, float y) const;
		void SetVec3(const std::string& name, const glm::vec3& value) const;
		void SetVec3(const std::string& name, float x, float y, float z) const;
		void SetVec4(const std::string& name, const glm::vec4& value) const;
		void SetVec4(const std::string& name, float x, float y, float z, float w) const;
		void SetMat2(const std::string& name, const glm::mat2& mat) const;
		void SetMat3(const std::string& name, const glm::mat3& mat) const;
		void SetMat4(const std::string& name, const glm::mat4& mat) const;
		int GetUniformLocation(const std::string& name) const;

	private:
		bool CompileShader(unsigned int& program, int glShaderType, std::string shaderType, std::string shaderPath);
	};

}
