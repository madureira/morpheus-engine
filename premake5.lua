workspace "Morpheus"
	architecture "x64"
	startproject "Editor"
	configurations { "Debug", "Release" }
	platforms { "x64", "x32" }
	files {
		".editorconfig"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Libraries/GLFW/include"
IncludeDir["Glad"] = "Libraries/Glad/include"
IncludeDir["Lua"] = "Libraries/lua/src"
IncludeDir["ImGui"] = "Libraries/imgui"
IncludeDir["FreeType2"] = "Libraries/freetype2/include"
IncludeDir["glm"] = "Libraries/glm"
IncludeDir["sol3"] = "Libraries/sol3/include"
IncludeDir["stb_image"] = "Libraries/stb_image/include"

group "Dependencies"
	include "Libraries/GLFW"
	include "Libraries/Glad"
	include "Libraries/lua"
	include "Libraries/imgui"
	include "Libraries/freetype2"

group ""

-- ENGINE
project "Engine"
	location "Morpheus/Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	objdir("Build/" .. outputdir)
	targetdir("Dist/" .. outputdir)

	pchheader "mepch.h"
	pchsource "Morpheus/%{prj.name}/Source/mepch.cpp"

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
		"%{IncludeDir.stb_image}"
	}

	links {
		"GLFW",
		"Glad",
		"Lua",
		"FreeType2"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter { "system:windows" }
		systemversion "latest"
		links { "opengl32" }

		defines {
			"ME_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter { "system:not windows" }
		links { "GL" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		optimize "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "On"
		optimize "Speed"


-- EDITOR
project "Editor"
	location "Morpheus/Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	objdir("Build/" .. outputdir)
	targetdir("Dist/" .. outputdir)

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
		"%{IncludeDir.stb_image}"
	}

	links {
		"Engine",
		"ImGui"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter { "system:windows" }
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		optimize "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		kind "WindowedApp"
		flags { entrypoint "mainCRTStartup" }
		optimize "Speed"


-- GAME
project "Game"
	location "Morpheus/Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	objdir("Build/" .. outputdir)
	targetdir("Dist/" .. outputdir)

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
		"%{IncludeDir.stb_image}"
	}

	links {
		"Engine"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter { "system:windows" }
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		optimize "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		kind "WindowedApp"
		flags { entrypoint "mainCRTStartup" }
		optimize "Speed"


-- Clean Function --
newaction {
	trigger = "clean",
	description = "clean the build",
	execute = function()
		print("Cleanning the build...")
		os.rmdir("./.vs")
		os.rmdir("./Build")
		os.rmdir("./Dist")
		os.rmdir("./Generated")
		os.remove("./Morpheus.sln")
		os.remove("./Makefile")
		print("Done.")
	end
}
