#pragma once

#include "Event.h"

namespace Morpheus {

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void onNotify(Event event) {};
	};

}