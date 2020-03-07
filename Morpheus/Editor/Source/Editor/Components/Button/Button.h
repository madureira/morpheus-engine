#pragma once

namespace Editor {

	class Button
	{
	public:
		static bool Draw(const char* icon, const char* label, const char* tooltip, bool disabled = false);

	private:
		static bool DrawButton(const char* icon, const char* label, const char* tooltip, bool disabled = false);
	};

}
