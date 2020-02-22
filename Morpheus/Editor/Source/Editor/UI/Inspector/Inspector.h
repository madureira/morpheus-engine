#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class ColorPicker;

	class Inspector : public UIComponent
	{
	private:
		ColorPicker* m_ColorPicker;

	public:
		Inspector(entt::registry& registry);
		~Inspector();

		void Draw(entt::registry& registry) override;
	};

}
