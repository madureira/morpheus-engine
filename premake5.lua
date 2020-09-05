include "./Tools/windows/premake/solution_items.lua"

workspace "Morpheus"
    architecture "x64"
    startproject "Editor"
    configurations {
        "Debug",
        "Release"
    }
    platforms {
        "x64",
        "x32"
    }
    flags { "MultiProcessorCompile" }
    solution_items { ".editorconfig" }

outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}"

IncludeDir = {}
IncludeDir["GLFW"] = "Libraries/GLFW/include"
IncludeDir["Glad"] = "Libraries/Glad/include"
IncludeDir["Lua"] = "Libraries/lua/src"
IncludeDir["ImGui"] = "Libraries/imgui"
IncludeDir["FreeType2"] = "Libraries/freetype2/include"
IncludeDir["glm"] = "Libraries/glm"
IncludeDir["sol3"] = "Libraries/sol3/include"
IncludeDir["stb_image"] = "Libraries/stb_image/include"
IncludeDir["entt"] = "Libraries/entt/include"
IncludeDir["spdlog"] = "Libraries/spdlog/include"
IncludeDir["nativefiledialog"] = "Libraries/nativefiledialog/src/include"
IncludeDir["nlohmann"] = "Libraries/nlohmann/include"
IncludeDir["TiledParser"] = "Libraries/TiledParser/include"

group "Dependencies"
    include "Libraries/GLFW"
    include "Libraries/Glad"
    include "Libraries/lua"
    include "Libraries/imgui"
    include "Libraries/freetype2"
    include "Libraries/nativefiledialog"
    include "Libraries/TiledParser"
group ""


-- ENGINE
project "Engine"
    location "Morpheus/Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    warnings "Off"
    objdir("Build/" .. outputdir)
    targetdir("Dist/" .. outputdir)
    pchheader "mepch.h"
    pchsource "Morpheus/%{prj.name}/Source/mepch.cpp"
    makesettings { "CC = gcc" }

    files {
        "Morpheus/%{prj.name}/Source/**.h",
        "Morpheus/%{prj.name}/Source/**.cpp",
        "Morpheus/%{prj.name}/Source/**.lua",
        "Morpheus/%{prj.name}/Assets/**"
    }

    includedirs {
        "Morpheus/%{prj.name}/Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Lua}",
        "%{IncludeDir.FreeType2}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.sol3}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.nlohmann}",
        "%{IncludeDir.TiledParser}"
    }

    links {
        "GLFW",
        "Glad",
        "Lua",
        "FreeType2",
        "TiledParser"
    }

    defines {
        "MORPHEUS_CORE",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
        links {
            "opengl32",
            "gdi32"
        }
        defines {
            "ME_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "system:not windows"
        links {
            "GL",
            "X11",
            "pthread",
            "dl",
            "atomic",
            "stdc++fs"
        }
        linkoptions { "-Wl,--allow-multiple-definition" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "Speed"
        defines { "NDEBUG" }


-- EDITOR
project "Editor"
    location "Morpheus/Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    warnings "Off"
    objdir("Build/" .. outputdir)
    targetdir("Dist/" .. outputdir)
    makesettings { "CC = gcc" }

    files {
        "Morpheus/%{prj.name}/Source/**.h",
        "Morpheus/%{prj.name}/Source/**.cpp",
        "Morpheus/%{prj.name}/Source/**.lua",
        "Morpheus/%{prj.name}/Assets/**"
    }

    includedirs {
        "Morpheus/%{prj.name}/Source",
        "Morpheus/Engine/Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Lua}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.FreeType2}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.sol3}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.nativefiledialog}",
        "%{IncludeDir.nlohmann}",
        "%{IncludeDir.TiledParser}"
    }

    links {
        "Engine",
        "ImGui",
        "nfd"
    }

    defines {
        "MORPHEUS_CORE",
        "MORPHEUS_EDITOR",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
        links {
            "opengl32",
            "gdi32"
        }
        postbuildcommands {
            "xcopy Assets ..\\..\\Dist\\%{cfg.system}\\%{cfg.buildcfg}\\%{cfg.platform}\\%{prj.name}\\Assets /e /i /s /y"
        }

    filter "system:not windows"
        links {
            "GL",
            "GLFW",
            "Glad",
            "Lua",
            "FreeType2",
            "TiledParser",
            "X11",
            "pthread",
            "dl",
            "atomic",
            "stdc++fs",
            "gtk-3",
            "gobject-2.0",
            "glib-2.0"
        }
        linkoptions {
            "-Wl,--allow-multiple-definition",
            "`pkg-config --libs gtk+-3.0`"
        }
        postbuildcommands {
            "cp -rf Assets ../../Dist/%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/Assets"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        kind "WindowedApp"
        runtime "Release"
        optimize "Speed"
        defines { "NDEBUG" }
        flags { entrypoint "mainCRTStartup" }


-- GAME
project "Game"
    location "Morpheus/Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    warnings "Off"
    objdir("Build/" .. outputdir)
    targetdir("Dist/" .. outputdir)
    makesettings { "CC = gcc" }

    files {
        "Morpheus/%{prj.name}/Source/**.h",
        "Morpheus/%{prj.name}/Source/**.cpp",
        "Morpheus/%{prj.name}/Source/**.lua",
        "Morpheus/%{prj.name}/Assets/**"
    }

    includedirs {
        "Morpheus/%{prj.name}/Source",
        "Morpheus/Engine/Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Lua}",
        "%{IncludeDir.FreeType2}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.sol3}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.nlohmann}",
        "%{IncludeDir.TiledParser}"
    }

    links {
        "Engine"
    }

    defines {
        "MORPHEUS_APP",
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
        links {
            "opengl32",
            "gdi32"
        }
        postbuildcommands {
            "xcopy Assets ..\\..\\Dist\\%{cfg.system}\\%{cfg.buildcfg}\\%{cfg.platform}\\%{prj.name}\\Assets /e /i /s /y"
        }

    filter "system:not windows"
        links {
            "GL",
            "GLFW",
            "Glad",
            "Lua",
            "FreeType2",
            "TiledParser",
            "X11",
            "pthread",
            "dl",
            "atomic",
            "stdc++fs"
        }
        linkoptions { "-Wl,--allow-multiple-definition" }
        postbuildcommands {
            "cp -rf Assets ../../Dist/%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/Assets"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        kind "WindowedApp"
        runtime "Release"
        optimize "Speed"
        defines { "NDEBUG" }
        flags { entrypoint "mainCRTStartup" }

newaction {
    trigger = "clean",
    description = "clean the build",
    execute = function()
        print("Cleanning the build...")
        os.remove("**/Makefile")
        os.remove("**/*.vcxproj*")
        os.remove("./Morpheus.sln")
        os.remove("./Makefile")
        os.remove("./*.vcxproj*")
        os.rmdir("./.vs")
        os.rmdir("./Build")
        os.rmdir("./Dist")
        os.rmdir("./Generated")
        os.rmdir("./Libraries/freetype2/bin")
        os.rmdir("./Libraries/freetype2/bin-int")
        os.rmdir("./Libraries/Glad/bin")
        os.rmdir("./Libraries/Glad/bin-int")
        os.rmdir("./Libraries/GLFW/bin")
        os.rmdir("./Libraries/GLFW/bin-int")
        os.rmdir("./Libraries/imgui/bin")
        os.rmdir("./Libraries/imgui/bin-int")
        os.rmdir("./Libraries/lua/bin")
        os.rmdir("./Libraries/lua/bin-int")
        os.rmdir("./Libraries/nativefiledialog/bin")
        os.rmdir("./Libraries/nativefiledialog/bin-int")
        os.rmdir("./Libraries/TiledParser/bin")
        os.rmdir("./Libraries/TiledParser/bin-int")
        print("Done.")
    end
}
