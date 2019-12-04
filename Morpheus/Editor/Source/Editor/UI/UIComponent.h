#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include "Vendors/IconsFontAwesome5.h"

namespace Editor {

	class UIComponent {
	public:
		virtual ~UIComponent() = default;
		virtual void Draw() = 0;
	};

}
