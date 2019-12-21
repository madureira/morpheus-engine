#pragma once

namespace Morpheus {

	struct InputStateComponent
	{
		bool UP;
		bool DOWN;
		bool LEFT;
		bool RIGHT;
		bool SPACE;
		bool LEFT_CONTROL;
		bool W;
		bool S;

		InputStateComponent()
			: UP(false)
			, DOWN(false)
			, LEFT(false)
			, RIGHT(false)
			, SPACE(false)
			, LEFT_CONTROL(false)
			, W(false)
			, S(false)
		{
		}
	};

}
