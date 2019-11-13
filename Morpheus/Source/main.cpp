#include "Core/Engine.h"
#include "Game/GameApp.h"
#include "Game/Config/Settings.h"


int main()
{
	Morpheus::Settings settings;
	/*
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script_file("Core/Config/settings.lua");

	bool isfullscreen = lua["config"]["fullscreen"];
	sol::table config = lua["config"];
	int width = config["resolution"]["width"];
	int height = config["resolution"]["height"];
	
	std::cout << "FullScreen: " << isfullscreen << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
	*/



	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Run();

	return 0;
}
