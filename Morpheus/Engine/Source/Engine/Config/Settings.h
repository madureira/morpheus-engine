#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <string>
#include <iostream>
#include <sol/sol.hpp>

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

    class Settings final
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
            : m_LuaState(nullptr)
            , m_WindowTitle("Morpheus Engine")
            , m_IsWindowFullScreen(false)
            , m_IsPrimaryMonitor(false)
            , m_WindowWidth(800)
            , m_WindowHeight(600)
            , m_FPS(60)
            , m_IsVSyncOn(false)
            , m_IsDebug(false)
        {
            m_LuaState = new sol::state();
            m_LuaState->open_libraries(sol::lib::base);

            sol::load_result settingsContent = m_LuaState->load_file(SETTINGS_FILE_PATH);

            if (IsSettingsValid(settingsContent))
            {
                LoadVariables();
            }
            else
            {
                ME_LOG_ERROR("Settings: Fail to parse {0}", SETTINGS_FILE_PATH);
            }
        }

        ~Settings()
        {
            delete m_LuaState;
        }

        inline std::string GetWindowTitle() const
        {
            return m_WindowTitle;
        }

        inline bool IsWindowFullscreen() const
        {
            return m_IsWindowFullScreen;
        }

        inline bool IsPrimaryMonitor() const
        {
            return m_IsPrimaryMonitor;
        }

        inline unsigned int GetWindowWidth() const
        {
            return m_WindowWidth;
        }

        inline unsigned int GetWindowHeight() const
        {
            return m_WindowHeight;
        }

        inline unsigned int GetMaxFPS() const
        {
            return m_FPS;
        }

        inline bool IsVSyncOn() const
        {
            return m_IsVSyncOn;
        }

        inline bool IsDebug() const
        {
            return m_IsDebug;
        }

        inline SettingsComponent GetSettings() const
        {
            return SettingsComponent{
                m_WindowTitle,
                m_IsWindowFullScreen,
                m_IsPrimaryMonitor,
                m_WindowWidth,
                m_WindowHeight,
                m_FPS,
                m_IsVSyncOn,
                m_IsDebug
            };
        }

    private:
        inline bool IsSettingsValid(sol::load_result& scriptSettings)
        {
            if (scriptSettings.valid())
            {
                sol::protected_function_result settings = scriptSettings();

                return settings.valid();
            }

            return false;
        }

        void LoadVariables()
        {
            sol::optional<std::string> windowTitle = (*m_LuaState)["config"]["window"]["title"];
            sol::optional<bool> windowFullScreen = (*m_LuaState)["config"]["window"]["fullscreen"];
            sol::optional<bool> windowPrimaryMonitor = (*m_LuaState)["config"]["window"]["primary_monitor"];
            sol::optional<unsigned int> windowResolutionWidth = (*m_LuaState)["config"]["window"]["resolution"]["width"];
            sol::optional<unsigned int> windowResolutionHeight = (*m_LuaState)["config"]["window"]["resolution"]["height"];
            sol::optional<unsigned int> fps = (*m_LuaState)["config"]["fps"];
            sol::optional<bool> vsync = (*m_LuaState)["config"]["vsync"];
            sol::optional<bool> debug = (*m_LuaState)["config"]["debug"];

            c_assert(windowTitle != sol::nullopt);
            c_assert(windowFullScreen != sol::nullopt);
            c_assert(windowPrimaryMonitor != sol::nullopt);
            c_assert(windowResolutionWidth != sol::nullopt);
            c_assert(windowResolutionHeight != sol::nullopt);
            c_assert(fps != sol::nullopt);
            c_assert(vsync != sol::nullopt);
            c_assert(debug != sol::nullopt);

            m_WindowTitle = windowTitle.value();
            m_IsWindowFullScreen = windowFullScreen.value();
            m_IsPrimaryMonitor = windowPrimaryMonitor.value();
            m_WindowWidth = windowResolutionWidth.value();
            m_WindowHeight = windowResolutionHeight.value();
            m_FPS = fps.value();
            m_IsVSyncOn = vsync.value();
            m_IsDebug = debug.value();
        }
    };

}
