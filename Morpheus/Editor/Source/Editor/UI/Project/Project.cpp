#include "Project.h"

namespace Editor {

	void Project::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_FOLDER" Project###project");
		ImGui::End();
	}

}
