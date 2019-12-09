#pragma once

#include <entt/entt.hpp>

namespace Morpheus {

	class Settings;
	class EventBus;
	class Window;

	class App
	{
	public:
		virtual ~App() = default;
		virtual void Initialize(Settings* pSettings, EventBus* pEventBus, Window* pWindow) = 0;
		virtual void OnFrameStarted(double deltaTime, int currentFrame, int frameRate, entt::registry& registry) = 0;
		virtual void FrameListener(double deltaTime, int currentFrame, int frameRate, entt::registry& registry) = 0;
	};

}
