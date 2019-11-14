#pragma once

#include <map>
#include <list>
#include <typeindex>
#include "MemberFunctionHandler.h"

namespace Morpheus {

	typedef std::list<HandlerFunctionBase*> HandlerList;
	class EventBus {
	private:
		std::map<std::type_index, HandlerList*> m_Subscribers;

	public:
		template<typename EventType>
		void publish(EventType* pEvent)
		{
			HandlerList* pHandlers = m_Subscribers[typeid(EventType)];

			if (pHandlers == nullptr)
			{
				return;
			}

			for (auto& handler : *pHandlers)
			{
				if (handler != nullptr)
				{
					handler->exec(pEvent);
				}
			}
		}

		template<class T, class EventType>
		void subscribe(T* pInstance, void(T::* memberFunction)(EventType*))
		{
			HandlerList* pHandlers = this->m_Subscribers[typeid(EventType)];

			//First time initialization
			if (pHandlers == nullptr)
			{
				pHandlers = new HandlerList();
				this->m_Subscribers[typeid(EventType)] = pHandlers;
			}

			pHandlers->push_back(new MemberFunctionHandler<T, EventType>(pInstance, memberFunction));
		}
	};

}
