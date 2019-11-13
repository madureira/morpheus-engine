#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <iostream>
#include <sol/sol.hpp>

namespace Morpheus {

	class Settings
	{
	private:
		const char* FILE_NAME = "Core/Config/settings.lua";
		sol::state* m_LuaState;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;

	public:
		Settings()
			: m_LuaState(new sol::state()),
			m_WindowWidth(800),
			m_WindowHeight(600)
		{
			this->m_LuaState->open_libraries(sol::lib::base);

			sol::load_result settingsContent = this->m_LuaState->script_file(FILE_NAME);

			if (!this->IsSettingsValid(settingsContent))
			{
				std::cout << "Error: Fail to parse Core/Config/settings.lua" << std::endl;
			}
		}

		~Settings()
		{
			delete this->m_LuaState;
		}

	private:
		bool IsSettingsValid(sol::load_result& settingsContent)
		{
			if (!settingsContent.valid()) {
				return false;
			}

			return true;
		}
	};

}