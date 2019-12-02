#pragma once

#include "Event.h"

namespace Morpheus {

	// This is the interface for MemberFunctionHandler that each specialization will use
	class HandlerFunctionBase {
	public:
		// Call the member function
		void Exec(Event* pEvent)
		{
			Call(pEvent);
		}
	private:
		// Implemented by MemberFunctionHandler
		virtual void Call(Event* pEvent) = 0;
	};

	template<class T, class EventType>
	class MemberFunctionHandler : public HandlerFunctionBase
	{
	public:
		typedef void (T::* MemberFunction)(EventType*);
		MemberFunctionHandler(T* pInstance, MemberFunction memberFunction)
			: m_Instance(pInstance),
			m_MemberFunction(memberFunction)
		{
		}

		void Call(Event* pEvent)
		{
			// Cast event to the correct type and call member function
			(this->m_Instance->*this->m_MemberFunction)(static_cast<EventType*>(pEvent));
		}
	private:
		// Pointer to class instance
		T* m_Instance;

		// Pointer to member function
		MemberFunction m_MemberFunction;
	};

}
