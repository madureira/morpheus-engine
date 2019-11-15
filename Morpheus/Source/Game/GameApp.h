#pragma once

#include "Core/App.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	public:
		~GameApp();
		void Initialize(Morpheus::EventBus* eventBus) override;
		void FrameListener(double deltaTime, int frame) override;
		void OnFrameStarted(double deltaTime, int frame) override;
	};

}
