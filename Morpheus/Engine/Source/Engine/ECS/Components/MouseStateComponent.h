#pragma once

namespace Morpheus {

	struct MouseStateComponent final
	{
		bool isLeftButtonPressed;
		bool isMiddleButtonPressed;
		bool isRightButtonPressed;
		double cursorX;
		double cursorY;
		double xOffSet;
		double yOffSet;

		MouseStateComponent()
			: isLeftButtonPressed(false)
			, isMiddleButtonPressed(false)
			, isRightButtonPressed(false)
			, cursorX(0.0)
			, cursorY(0.0)
			, xOffSet(0.0)
			, yOffSet(0.0)
		{
		}
	};

}
