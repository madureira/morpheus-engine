#include "GameApp.h"
#include "Core/Event/EventBus.h"

namespace Game {

	void GameApp::Initialize(Morpheus::EventBus* pEventBus)
	{
		this->m_EventBus = pEventBus;
	}

	void GameApp::OnFrameStarted()
	{
		
	}

	GameApp::~GameApp()
	{

	}

}
