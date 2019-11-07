#pragma once

#include "Core/App/App.h"

namespace Game {

	class GameApp : public Morpheus::App
	{
	public:
		void Initialize(Morpheus::EventBus* eventBus) override;
		void OnFrameStarted() override;
	};

}
