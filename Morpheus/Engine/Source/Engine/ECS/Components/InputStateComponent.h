#pragma once

namespace Morpheus {

	struct InputStateComponent
	{
		bool UP;
		bool DOWN;
		bool LEFT;
		bool RIGHT;
		bool SPACE;
		bool W;
		bool S;

		InputStateComponent()
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

}
