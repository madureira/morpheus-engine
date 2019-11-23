#include <iostream>
#include "Input.h"
#include "Core/Event/EventBus.h"
#include "Core/Input/Keyboard/Keys.h"
#include "InputEvent.h"

namespace Morpheus {

	Input::Input(EventBus* pEventBus)
		: m_EventBus(pEventBus),
		m_IsUpKeyPressed(false),
		m_IsDownKeyPressed(false),
		m_IsLeftKeyPressed(false),
		m_IsRightKeyPressed(false),
		m_IsSpaceKeyPressed(false),
		m_IsAKeyPressed(false),
		m_IsWKeyPressed(false),
		m_IsDKeyPressed(false),
		m_IsSKeyPressed(false)
	{
		this->m_EventBus->subscribe(this, &Input::OnKeyboardEvent);
	}

	void Input::OnKeyboardEvent(KeyboardEvent* pEvent)
	{
		this->UpdateKeyStatus(pEvent->GetKey(), pEvent->GetAction());

		/*
		std::cout << "\r" << "UP: " << this->m_IsUpKeyPressed
			<< ", DOWN: " << this->m_IsDownKeyPressed
			<< ", LEFT: " << this->m_IsLeftKeyPressed
			<< ", RIGHT: " << this->m_IsRightKeyPressed
			<< ", SPACE: " << this->m_IsSpaceKeyPressed
			<< ", A: " << this->m_IsAKeyPressed
			<< ", W: " << this->m_IsWKeyPressed
			<< ", D: " << this->m_IsDKeyPressed
			<< ", S: " << this->m_IsSKeyPressed;
			*/

		InputState state;
		state.UP = this->m_IsUpKeyPressed;
		state.DOWN = this->m_IsDownKeyPressed;
		state.LEFT = this->m_IsLeftKeyPressed;
		state.RIGHT = this->m_IsRightKeyPressed;

		InputEvent inputEvent(state);
		this->m_EventBus->publish(&inputEvent);
	}

	void Input::UpdateKeyStatus(int key, KeyboardEvent::Action action)
	{
		bool isPressing = (action == KeyboardEvent::Action::PRESS);

		switch (key)
		{
		case Keys::UP:
			this->m_IsUpKeyPressed = isPressing;
			break;
		case Keys::DOWN:
			this->m_IsDownKeyPressed = isPressing;
			break;
		case Keys::LEFT:
			this->m_IsLeftKeyPressed = isPressing;
			break;
		case Keys::RIGHT:
			this->m_IsRightKeyPressed = isPressing;
			break;
		case Keys::SPACE:
			this->m_IsSpaceKeyPressed = isPressing;
			break;
		case Keys::A:
			this->m_IsAKeyPressed = isPressing;
			break;
		case Keys::W:
			this->m_IsWKeyPressed = isPressing;
			break;
		case Keys::D:
			this->m_IsDKeyPressed = isPressing;
			break;
		case Keys::S:
			this->m_IsSKeyPressed = isPressing;
			break;
		default:
			break;
		}
	}

}
