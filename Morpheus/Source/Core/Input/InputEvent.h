#pragma once

#include "Core/Event/Event.h"

namespace Morpheus {

	struct InputState
	{
		int UP;
		int DOWN;
		int LEFT;
		int RIGHT;
	};

	class InputEvent : public Event {
	private:
		InputState m_InputState;

	public:
		InputEvent(InputState inputState)
		{
			this->m_InputState = inputState;
		}

		const InputState GetState() const
		{
			return this->m_InputState;
		}
	};
}
