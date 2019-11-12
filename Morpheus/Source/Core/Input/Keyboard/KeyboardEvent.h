#pragma once

#include "Core/Event/Event.h"

namespace Morpheus {

	class KeyboardEvent : public Event {
	public:
		enum class Action
		{
			PRESS,
			RELEASE
		};

		KeyboardEvent(Action action, int key) : m_Action(action), m_Key(key) {}
		inline Action GetAction() const { return m_Action; }
		inline int GetKey() const { return m_Key; }

	private:
		Action m_Action;
		int m_Key;
	};
}
