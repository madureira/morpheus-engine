#pragma once

namespace Morpheus {

	struct InputStateComponent final
	{
		bool UP;
		bool DOWN;
		bool LEFT;
		bool RIGHT;
		bool SPACE;
		bool LEFT_CONTROL;
		bool LEFT_SHIFT;
		bool W;
		bool S;

		InputStateComponent()
			: UP(false)
			, DOWN(false)
			, LEFT(false)
			, RIGHT(false)
			, SPACE(false)
			, LEFT_CONTROL(false)
			, LEFT_SHIFT(false)
			, W(false)
			, S(false)
		{
		}
	};

}
