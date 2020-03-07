#pragma once

#include "Editor/UI/UIContainer.h"

namespace Editor {

	class ColorPicker;

	class Inspector : public UIContainer
	{
	private:
		ColorPicker* m_ColorPicker;

	public:
		Inspector(entt::registry& registry);
		~Inspector();

		void Draw(entt::registry& registry) override;
	};

}
