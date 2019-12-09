#pragma once

#include "Editor/UI/UIComponent.h"
#include "Engine/ECS/ECS.h"
#include <glm/vec4.hpp>
#include <string>

namespace Editor {

	class ColorPicker : public UIComponent
	{
	private:
		const char* m_Label;
		ImVec4 m_Color;
		entt::entity m_Entity;

	public:
		ColorPicker(const char* label, entt::registry& registry, entt::entity& entity);
		void Draw(entt::registry& registry) override;
	};

}
