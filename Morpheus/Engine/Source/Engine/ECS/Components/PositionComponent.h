#pragma once

namespace Morpheus {

	struct PositionComponent final
	{
		float x;
		float y;

		PositionComponent(float posX, float posY)
			: x(posX)
			, y(posY)
		{
		}
	};

}
