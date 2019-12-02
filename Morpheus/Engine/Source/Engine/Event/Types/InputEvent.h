#pragma once

#include "../Event.h"

namespace Morpheus {

	struct InputState
	{
		bool UP;
		bool DOWN;
		bool LEFT;
		bool RIGHT;
		bool SPACE;
		bool W;
		bool S;

		InputState()
			: UP(false),
			DOWN(false),
			LEFT(false),
			RIGHT(false),
			SPACE(false),
			W(false),
			S(false)
		{
		}
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
