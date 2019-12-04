#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/Shader/Shader.h"
#include "Engine/Config/Settings.h"
#include <glm/vec4.hpp>

namespace Editor {

	class Viewport : public UIComponent
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		float m_Vertices[9];
		Morpheus::Shader* m_Shader;
		unsigned int m_FBO;
		unsigned int m_TextureColorBuffer;
		glm::vec4 m_FrameBufferRect;
		Morpheus::Settings* m_Settings;
		glm::vec4 m_Color;

	public:
		Viewport(Morpheus::Settings* pSettings);
		~Viewport();
		void ChangeColor(glm::vec4& color);
		void Draw() override;
	};

}
