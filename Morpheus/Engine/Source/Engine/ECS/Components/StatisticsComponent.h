#pragma once

namespace Morpheus {

	struct StatisticsComponent final
	{
		int frameRate = 0;
		double frameDeltaTime = 0.0;
		int drawCalls = 0;
		int vertices = 0;

		StatisticsComponent()
		{
		}
	};

}
