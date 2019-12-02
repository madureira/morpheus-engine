#pragma once

namespace Morpheus {

	class Settings;
	class EventBus;

	class App
	{
	public:
		virtual ~App() = default;
		virtual void Initialize(Morpheus::Settings* pSettings, Morpheus::EventBus* pEventBus) = 0;
		virtual void OnFrameStarted(double deltaTime, int frame) = 0;
		virtual void FrameListener(double deltaTime, int frame) = 0;
	};

}
