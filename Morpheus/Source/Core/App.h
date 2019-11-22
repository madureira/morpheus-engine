#pragma once

namespace Morpheus {

	class EventBus;
	class Settings;

	class App
	{
	public:
		virtual ~App() = default;
		virtual void Initialize(Morpheus::EventBus* pEventBus, Morpheus::Settings* pSettings) = 0;
		virtual void OnFrameStarted(double deltaTime, int frame) = 0;
		virtual void FrameListener(double deltaTime, int frame) = 0;
	};

}
