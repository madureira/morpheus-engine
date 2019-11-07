#include "Core/Engine.h"
#include "Game/GameApp.h"

int main()
{
	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Run();

	return 0;
}
