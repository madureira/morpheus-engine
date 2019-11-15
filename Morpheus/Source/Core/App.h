#pragma once

namespace Morpheus {

	class EventBus;

	class App
	{
	protected:
		EventBus* m_EventBus;

	public:
		virtual ~App() = default;
		virtual void Initialize(Morpheus::EventBus* eventBus) = 0;
		virtual void FrameListener(double deltaTime, int frame) = 0;
		virtual void OnFrameStarted(double deltaTime, int frame) = 0;
	};

}
