#pragma once

#include <imgui.h>

namespace Editor {

	class ColorPicker
	{
	public:
		static void Draw(const char* label, ImVec4& color);
	};

}
