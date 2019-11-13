#include "Core/Engine.h"
#include "Game/GameApp.h"
#include "Game/Config/Settings.h"


int main()
{
	Morpheus::Settings settings;
	
	std::cout << "FullScreen: " << settings.GetWindowFullscreen() << std::endl;
	std::cout << "Width: " << settings.GetWindowWidth() << std::endl;
	std::cout << "Height: " << settings.GetWindowHeight() << std::endl;

	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Run();

	return 0;
}
