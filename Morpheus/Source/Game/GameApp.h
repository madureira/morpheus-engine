#pragma once

#include "Core/App.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	public:
		~GameApp();
		void Initialize(Morpheus::EventBus* eventBus) override;
		void OnFrameStarted() override;
	};

}
