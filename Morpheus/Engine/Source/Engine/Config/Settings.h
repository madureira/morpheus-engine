#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>
#include <iostream>
#include <string>

#include "Engine/ECS/ECS.h"

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
		const char* SETTINGS_FILE_PATH = "Assets/settings.lua";
		sol::state* m_LuaState;
		std::string m_WindowTitle;
		bool m_IsWindowFullScreen;
		bool m_IsPrimaryMonitor;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;
		unsigned int m_FPS;
		bool m_IsVSyncOn;
		bool m_IsDebug;

	public:
		Settings(entt::registry& registry)
			: m_LuaState(nullptr),
			m_WindowTitle("Morpheus Engine"),
			m_IsWindowFullScreen(false),
			m_IsPrimaryMonitor(false),
			m_WindowWidth(800),
			m_WindowHeight(600),
			m_FPS(30),
			m_IsVSyncOn(false),
			m_IsDebug(false)
		{
			this->m_LuaState = new sol::state();
			this->m_LuaState->open_libraries(sol::lib::base);

			sol::load_result settingsContent = this->m_LuaState->load_file(SETTINGS_FILE_PATH);

			if (!this->IsSettingsValid(settingsContent, registry))
			{
				ME_CORE_ERROR("Settings: Fail to parse {0}", SETTINGS_FILE_PATH);
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

		inline bool IsWindowFullscreen() const
		{
			return this->m_IsWindowFullScreen;
		}

		inline bool IsPrimaryMonitor() const
		{
			return this->m_IsPrimaryMonitor;
		}

		inline unsigned int GetWindowWidth() const
		{
			return this->m_WindowWidth;
		}

		inline unsigned int GetWindowHeight() const
		{
			return this->m_WindowHeight;
		}

		inline unsigned int GetMaxFPS() const
		{
			return this->m_FPS;
		}

		inline bool IsVSyncOn() const
		{
			return this->m_IsVSyncOn;
		}

		inline bool IsDebug() const
		{
			return this->m_IsDebug;
		}

		inline SettingsComponent GetSettings() const
		{
			return SettingsComponent{
				this->m_WindowTitle,
				this->m_IsWindowFullScreen,
				this->m_IsPrimaryMonitor,
				this->m_WindowWidth,
				this->m_WindowHeight,
				this->m_FPS,
				this->m_IsVSyncOn,
				this->m_IsDebug
			};
		}

	private:
		inline bool IsSettingsValid(sol::load_result& scriptSettings, entt::registry& registry)
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
			sol::optional<bool> windowPrimaryMonitor = (*this->m_LuaState)["config"]["window"]["primary_monitor"];
			sol::optional<unsigned int> windowResolutionWidth = (*this->m_LuaState)["config"]["window"]["resolution"]["width"];
			sol::optional<unsigned int> windowResolutionHeight = (*this->m_LuaState)["config"]["window"]["resolution"]["height"];
			sol::optional<unsigned int> fps = (*this->m_LuaState)["config"]["fps"];
			sol::optional<bool> vsync = (*this->m_LuaState)["config"]["vsync"];
			sol::optional<bool> debug = (*this->m_LuaState)["config"]["debug"];

			c_assert(windowTitle != sol::nullopt);
			c_assert(windowFullScreen != sol::nullopt);
			c_assert(windowPrimaryMonitor != sol::nullopt);
			c_assert(windowResolutionWidth != sol::nullopt);
			c_assert(windowResolutionHeight != sol::nullopt);
			c_assert(fps != sol::nullopt);
			c_assert(vsync != sol::nullopt);
			c_assert(debug != sol::nullopt);

			this->m_WindowTitle = windowTitle.value();
			this->m_IsWindowFullScreen = windowFullScreen.value();
			this->m_IsPrimaryMonitor = windowPrimaryMonitor.value();
			this->m_WindowWidth = windowResolutionWidth.value();
			this->m_WindowHeight = windowResolutionHeight.value();
			this->m_FPS = fps.value();
			this->m_IsVSyncOn = vsync.value();
			this->m_IsDebug = debug.value();

			return true;
		}
	};

}
