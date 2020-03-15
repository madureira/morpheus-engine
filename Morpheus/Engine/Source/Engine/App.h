#pragma once

#include "ECS/ECS.h"

namespace Morpheus {

	class App
	{
	public:
		virtual ~App() = default;

		virtual void Initialize(entt::registry& registry) = 0;
		virtual void OnFrameStarted(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) = 0;
		virtual void FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) = 0;
	};

}
