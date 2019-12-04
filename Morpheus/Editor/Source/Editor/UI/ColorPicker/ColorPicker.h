#pragma once

#include "Editor/UI/UIComponent.h"
#include <glm/vec4.hpp>
#include <string>

namespace Editor {

	class ColorPicker : public UIComponent
	{
	private:
		const char* m_Label;
		ImVec4 m_Color;

	public:
		ColorPicker(const char* label);
		void Draw() override;
		glm::vec4 GetSelectedColor();
	};

}
