#pragma once

#include "./ECS/ECS.h"

namespace Morpheus {

	class Settings;
	class Window;

	class App
	{
	public:
		virtual ~App() = default;
		virtual void Initialize(Settings* pSettings, Window* pWindow, entt::registry& registry) = 0;
		virtual void OnFrameStarted(double deltaTime, int currentFrame, int frameRate, entt::registry& registry) = 0;
		virtual void FrameListener(double deltaTime, int currentFrame, int frameRate, entt::registry& registry) = 0;
	};

}
