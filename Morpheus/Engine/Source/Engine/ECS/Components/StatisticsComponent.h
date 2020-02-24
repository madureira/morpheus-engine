#pragma once

namespace Morpheus {

	struct StatisticsComponent
	{
		int frameRate = 0;
		int drawCalls = 0;
		int vertices = 0;

		StatisticsComponent()
		{
		}
	};

}
