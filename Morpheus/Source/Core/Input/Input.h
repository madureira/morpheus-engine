#pragma once

#include "Core/Input/Keyboard/KeyboardEvent.h"

namespace Morpheus {

	class EventBus;

	class Input
	{
	private:
		EventBus* m_EventBus;
		bool m_KeyUpPressed;
		bool m_KeyDownPressed;
		bool m_KeyLeftPressed;
		bool m_KeyRightPressed;

	public:
		Input(EventBus* pEventBus);

	private:
		void OnKeyboardEvent(KeyboardEvent* pEvent);
		void UpdateKeyStatus(int key, KeyboardEvent::Action action);
	};

}
