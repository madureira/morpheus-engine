#include "GameApp.h"

namespace Game {

	void GameApp::Initialize(Morpheus::EventBus* eventBus)
	{
		this->m_EventBus = eventBus;
	}

	void GameApp::OnFrameStarted()
	{

	}

}
