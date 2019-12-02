#pragma once

namespace Morpheus {

	class Settings;
	class EventBus;
	class Window;

	class App
	{
	public:
		virtual ~App() = default;
		virtual void Initialize(Settings* pSettings, EventBus* pEventBus, Window* pWindow) = 0;
		virtual void OnFrameStarted(double deltaTime, int frame) = 0;
		virtual void FrameListener(double deltaTime, int frame) = 0;
	};

}
