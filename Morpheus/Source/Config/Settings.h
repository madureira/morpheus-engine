#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>
#include <iostream>
#include <string>

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
		const char* SETTINGS_FILE_PATH = "Config/settings.lua";
		sol::state* m_LuaState;
		std::string m_WindowTitle;
		bool m_WindowFullScreen;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;
		bool m_RenderVSync;

	public:
		Settings()
			: m_LuaState(nullptr),
			m_WindowTitle("Morpheus Engine"),
			m_WindowFullScreen(false),
			m_WindowWidth(800),
			m_WindowHeight(600),
			m_RenderVSync(false)
		{
			this->m_LuaState = new sol::state();
			this->m_LuaState->open_libraries(sol::lib::base);

			sol::load_result settingsContent = this->m_LuaState->load_file(SETTINGS_FILE_PATH);

			if (!this->IsSettingsValid(settingsContent))
			{
				std::cout << "Error: Fail to parse " << SETTINGS_FILE_PATH << std::endl;
			}
		}

		~Settings()
		{
			delete this->m_LuaState;
		}

		inline std::string GetWindowTitle() const
		{
			return this->m_WindowTitle;
		}

		inline bool GetWindowFullscreen() const
		{
			return this->m_WindowFullScreen;
		}

		inline unsigned int GetWindowWidth() const
		{
			return this->m_WindowWidth;
		}

		inline unsigned int GetWindowHeight() const
		{
			return this->m_WindowHeight;
		}

		inline bool GetRenderVSync() const
		{
			return this->m_RenderVSync;
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

			sol::optional<std::string> windowTitle = (*this->m_LuaState)["config"]["window"]["title"];
			sol::optional<bool> windowFullScreen = (*this->m_LuaState)["config"]["window"]["fullscreen"];
			sol::optional<unsigned int> windowResolutionWidth = (*this->m_LuaState)["config"]["window"]["resolution"]["width"];
			sol::optional<unsigned int> windowResolutionHeight = (*this->m_LuaState)["config"]["window"]["resolution"]["height"];
			sol::optional<bool> renderVSync = (*this->m_LuaState)["config"]["render"]["vsync"];

			c_assert(windowTitle != sol::nullopt);
			c_assert(windowFullScreen != sol::nullopt);
			c_assert(windowResolutionWidth != sol::nullopt);
			c_assert(windowResolutionHeight != sol::nullopt);
			c_assert(renderVSync != sol::nullopt);

			this->m_WindowTitle = windowTitle.value();
			this->m_WindowFullScreen = windowFullScreen.value();
			this->m_WindowWidth = windowResolutionWidth.value();
			this->m_WindowHeight = windowResolutionHeight.value();
			this->m_RenderVSync = renderVSync.value();

			return true;
		}
	};

}
