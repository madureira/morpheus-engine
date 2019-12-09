#include "Console.h"

namespace Editor {

	void Console::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_TERMINAL" Console###console");
		ImGui::End();
	}

}
