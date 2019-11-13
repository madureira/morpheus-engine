#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>
#include <iostream>

#define c_assert(condition) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << std::endl; \
            std::terminate(); \
        } \
    } while (false)


namespace Morpheus {

	class Settings
	{
	private:
		const char* FILE_NAME = "Game/Config/settings.lua";
		sol::state* m_LuaState;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;
		unsigned int m_WindowFullScreen;

	public:
		Settings()
			: m_LuaState(new sol::state()),
			m_WindowWidth(800),
			m_WindowHeight(600),
			m_WindowFullScreen(false)
		{
			this->m_LuaState->open_libraries(sol::lib::base);

			sol::load_result settingsContent = this->m_LuaState->load_file(FILE_NAME);

			if (!this->IsSettingsValid(settingsContent))
			{
				std::cout << "Error: Fail to parse Game/Config/settings.lua" << std::endl;
			}
		}

		~Settings()
		{
			delete this->m_LuaState;
		}

		inline unsigned int GetWindowWidth() const
		{
			return this->m_WindowWidth;
		}

		inline unsigned int GetWindowHeight() const
		{
			return this->m_WindowHeight;
		}

		inline bool GetWindowFullscreen() const
		{
			return this->m_WindowFullScreen;
		}

	private:
		inline bool IsSettingsValid(sol::load_result& scriptSettings)
		{
			if (!scriptSettings.valid()) {
				return false;
			}

			sol::protected_function_result settings = scriptSettings();

			if (!settings.valid()) {
				return false;
			}

			sol::optional<unsigned int> windowResolutionWidth = (*this->m_LuaState)["config"]["window"]["resolution"]["width"];
			sol::optional<unsigned int> windowResolutionHeight = (*this->m_LuaState)["config"]["window"]["resolution"]["height"];
			sol::optional<bool> windowFullScreen = (*this->m_LuaState)["config"]["window"]["fullscreen"];

			c_assert(windowResolutionWidth != sol::nullopt);
			c_assert(windowResolutionHeight != sol::nullopt);
			c_assert(windowFullScreen != sol::nullopt);

			this->m_WindowWidth = windowResolutionWidth.value();
			this->m_WindowHeight = windowResolutionHeight.value();
			this->m_WindowFullScreen = windowFullScreen.value();

			return true;
		}
	};

}