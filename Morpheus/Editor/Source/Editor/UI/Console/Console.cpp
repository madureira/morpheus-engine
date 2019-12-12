#include "Console.h"

namespace Editor {

	void Console::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_TERMINAL" Console###console");
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.00f, 0.00f , 0.00f , 1.00f });
			ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			{
				auto messageStart = Morpheus::CustomLogSink_mt::s_MessageBuffer.begin() + Morpheus::CustomLogSink_mt::s_MessageBufferBegin;

				for (auto message = messageStart; message != Morpheus::CustomLogSink_mt::s_MessageBuffer.end(); message++)
				{
					if (*messageStart) // If contains old message here
					{
						Morpheus::LogColor color = (*message)->GetLogColor();
						ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
						ImGui::TextUnformatted((*message)->m_Message.c_str());
						ImGui::PopStyleColor();
					}
				}

				if (Morpheus::CustomLogSink_mt::s_MessageBufferBegin != 0) // Skipped first messages in vector
				{
					for (auto message = Morpheus::CustomLogSink_mt::s_MessageBuffer.begin(); message != messageStart; message++)
					{
						if (*message)
						{
							Morpheus::LogColor color = (*message)->GetLogColor();
							ImGui::PushStyleColor(ImGuiCol_Text, { color.r, color.g, color.b, color.a });
							ImGui::TextUnformatted((*message)->m_Message.c_str());
							ImGui::PopStyleColor();
						}
					}
				}

				if (Morpheus::CustomLogSink_mt::s_RequestScrollToBottom && ImGui::GetScrollMaxY() > 0)
				{
					ImGui::SetScrollY(ImGui::GetScrollMaxY());
					Morpheus::CustomLogSink_mt::s_RequestScrollToBottom = false;
				}
			}
			ImGui::EndChild();
			ImGui::PopStyleColor();
		}
		ImGui::End();
	}

}
