#pragma once

#include "Core/Event/EventBus.h"
#include "Core/App.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	private:
		Morpheus::EventBus* m_EventBus;

	public:
		~GameApp();
		void Initialize(Morpheus::EventBus* eventBus) override;
		void OnFrameStarted(double deltaTime, int frame) override;
		void FrameListener(double deltaTime, int frame) override;
	};

}
