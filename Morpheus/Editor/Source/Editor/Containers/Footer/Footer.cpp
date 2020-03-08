#include "Footer.h"
#include <Engine/Util/NumberUtil.h>

namespace Editor {

	void Footer::Render(entt::registry& registry)
	{
		auto& statisticsEntity = registry.ctx<Morpheus::StatisticsEntity>();
		auto& statistics = registry.get<Morpheus::StatisticsComponent>(statisticsEntity.id);

		ImGuiIO& io = ImGui::GetIO();

		static bool showFooter = true;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - 32.0f));

		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 25.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

		ImGui::Begin("Footer", &showFooter, windowFlags);
		{
			ImGui::Dummy(ImVec2(0.0f, 2.0f));
			ImGui::Text("Status");

			ImGui::SameLine((float)io.DisplaySize.x - 525.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.725f, 0.725f, 0.725f, 1.0f));
			ImGui::Text("Draw calls: %i", statistics.drawCalls);
			ImGui::PopStyleColor();

			std::string numberOfQuads = Morpheus::NumberUtil::FormatThousandSeparator(statistics.vertices / 6);

			ImGui::SameLine((float)io.DisplaySize.x - 425.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.235f, 0.588f, 0.686f, 1.0f));
			ImGui::Text("Quads: %s", numberOfQuads.c_str());
			ImGui::PopStyleColor();

			std::string numberOfVertices = Morpheus::NumberUtil::FormatThousandSeparator(statistics.vertices);

			ImGui::SameLine((float)io.DisplaySize.x - 325.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.800f, 0.408f, 0.160f, 1.0f));
			ImGui::Text("Vertices: %s", numberOfVertices.c_str());
			ImGui::PopStyleColor();

			ImGui::SameLine((float)io.DisplaySize.x - 210.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 0.7f, 0.9f, 1.0f));
			ImGui::Text("%s ms/frame", std::to_string(statistics.frameDeltaTime).c_str());
			ImGui::PopStyleColor();

			ImGui::SameLine((float)io.DisplaySize.x - 70.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.9f, 0.2f, 1.0f));
			ImGui::Text("FPS: %i", statistics.frameRate);
			ImGui::PopStyleColor();
		}
		ImGui::End();

		ImGui::PopStyleVar();
	}

}
