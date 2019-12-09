#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class Actionbar : public UIComponent
	{
	private:
		bool m_IsPlaying;
		int m_FrameRate;

	public:
		Actionbar();
		void UpdateFrameRate(int frameRate);
		void Draw() override;

	private:
		bool DrawButton(const char* icon, const char* label, bool disabled);
	};

}
