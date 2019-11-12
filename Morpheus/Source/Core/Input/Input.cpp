#include <iostream>
#include "Input.h"
#include "Core/Event/EventBus.h"
#include "Core/Input/Keyboard/Keys.h"

namespace Morpheus {

	Input::Input(EventBus* pEventBus)
		: m_EventBus(pEventBus),
		m_KeyUpPressed(false),
		m_KeyDownPressed(false),
		m_KeyLeftPressed(false),
		m_KeyRightPressed(false)
	{
		this->m_EventBus->subscribe(this, &Input::OnKeyboardEvent);
	}

	void Input::OnKeyboardEvent(KeyboardEvent* pEvent)
	{
		this->UpdateKeyStatus(pEvent->GetKey(), pEvent->GetAction());

		std::cout << "\r" << "UP: " << this->m_KeyUpPressed
			<< ", DOWN: " << this->m_KeyDownPressed
			<< ", LEFT: " << this->m_KeyLeftPressed
			<< ", RIGHT: " << this->m_KeyRightPressed;
	}

	void Input::UpdateKeyStatus(int key, KeyboardEvent::Action action)
	{
		bool isPressing = action == KeyboardEvent::Action::PRESS;

		switch (key)
		{
		case Keys::UP:
			this->m_KeyUpPressed = isPressing;
			break;
		case Keys::DOWN:
			this->m_KeyDownPressed = isPressing;
			break;
		case Keys::LEFT:
			this->m_KeyLeftPressed = isPressing;
			break;
		case Keys::RIGHT:
			this->m_KeyRightPressed = isPressing;
			break;
		default:
			break;
		}
	}

}