#include "Core/Engine.h"
#include "Game/GameApp.h"
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

int main()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('bark bark bark!')");

	Morpheus::Engine engine;
	engine.Initialize(new Game::GameApp);
	engine.Run();

	return 0;
}
