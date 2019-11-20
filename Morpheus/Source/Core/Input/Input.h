#pragma once

#include "Core/Input/Keyboard/KeyboardEvent.h"

namespace Morpheus {

	class EventBus;

	class Input
	{
	private:
		EventBus* m_EventBus;
		bool m_IsUpKeyPressed;
		bool m_IsDownKeyPressed;
		bool m_IsLeftKeyPressed;
		bool m_IsRightKeyPressed;
		bool m_IsSpaceKeyPressed;
		bool m_IsAKeyPressed;
		bool m_IsWKeyPressed;
		bool m_IsDKeyPressed;
		bool m_IsSKeyPressed;

	public:
		Input(EventBus* pEventBus);

	private:
		void OnKeyboardEvent(KeyboardEvent* pEvent);
		void UpdateKeyStatus(int key, KeyboardEvent::Action action);
	};

}
