#include "Core/Engine.h"
#include "Game/GameApp.h"

#if defined(_WIN32)
extern "C"
{
	// Force to use dedicated GPU
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main()
{
	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Start();

	return 0;
}
