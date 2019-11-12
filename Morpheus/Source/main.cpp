#include "Core/Engine.h"
#include "Game/GameApp.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <iostream>
#include <string>
#include "Core/Util/FileUtil.h"
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
	std::cout << std::filesystem::current_path().string().c_str() << std::endl;

	std::string path = "./";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path() << std::endl;

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	std::string engineConfig = Morpheus::FileUtil::ReadFile("Config/engine.lua");

	std::string text = R"(
		config = {
			fullscreen = true,
			resolution = {
				width = 800,
				height = 600
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
