#include "GameApp.h"

namespace Game {

	void GameApp::Initialize(Morpheus::EventBus* pEventBus)
	{
		this->m_EventBus = pEventBus;
	}

	void GameApp::OnFrameStarted(double deltaTime, int frame)
	{
	}

	void GameApp::FrameListener(double deltaTime, int frame)
	{
	}

	GameApp::~GameApp()
	{
	}

}