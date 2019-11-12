#include "Core/Engine.h"
#include "Game/GameApp.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <string>

int main()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	std::string text = R"(
		config = {
			fullscreen = true,
			resolution = {
				width = 1024,
				height = 768
			}
		}
	)";

	lua.script(text);

	bool isfullscreen = lua["config"]["fullscreen"];
	sol::table config = lua["config"];
	int width = config["resolution"]["width"];
	int height = config["resolution"]["height"];
	
	std::cout << "FullScreen: " << isfullscreen << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;

	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Run();

	return 0;
}
