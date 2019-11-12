#pragma once

#include <map>
#include <list>
#include <typeindex>
#include "MemberFunctionHandler.h"

namespace Morpheus {

	typedef std::list<HandlerFunctionBase*> HandlerList;
	class EventBus {
	private:
		std::map<std::type_index, HandlerList*> subscribers;

	public:
		template<typename EventType>
		void publish(EventType* pEvent)
		{
			HandlerList* pHandlers = subscribers[typeid(EventType)];

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
		void subscribe(T* instance, void (T::* memberFunction)(EventType*))
		{
			HandlerList* pHandlers = subscribers[typeid(EventType)];

			//First time initialization
			if (pHandlers == nullptr)
			{
				pHandlers = new HandlerList();
				subscribers[typeid(EventType)] = pHandlers;
			}

			pHandlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
		}
	};

}

