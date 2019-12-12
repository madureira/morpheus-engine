#include "Console.h"

namespace Editor {

	void Console::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_TERMINAL" Console###console");
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.00f, 0.00f , 0.00f , 1.00f });
			ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			{
				for (auto message : Morpheus::CustomLogSink_mt::s_MessageBuffer)
				{
					if (message)
					{
						Morpheus::LogColor color = message->GetLogColor();
						ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
						ImGui::TextUnformatted(message->m_Message.c_str());
						ImGui::PopStyleColor();
					}
				}
			}
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}
		ImGui::End();
	}

}
