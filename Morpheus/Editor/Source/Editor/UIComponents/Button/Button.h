#pragma once

namespace Editor {

	class Button final
	{
	public:
		static bool Render(const char* icon, const char* label, const char* tooltip, bool disabled = false);

	private:
		static bool RenderButton(const char* icon, const char* label, const char* tooltip, bool disabled = false);
	};

}
