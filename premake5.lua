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
IncludeDir["entt"] = "Libraries/entt/include"
IncludeDir["spdlog"] = "Libraries/spdlog/include"
IncludeDir["nativefiledialog"] = "Libraries/nativefiledialog/src/include"
IncludeDir["nlohmann"] = "Libraries/nlohmann/include"

group "Dependencies"
	include "Libraries/GLFW"
	include "Libraries/Glad"
	include "Libraries/lua"
	include "Libraries/imgui"
	include "Libraries/freetype2"
	include "Libraries/nativefiledialog"

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
		"%{IncludeDir.nlohmann}"
	}

	links {
		"GLFW",
		"Glad",
		"Lua",
		"FreeType2"
	}

	defines {
		"MORPHEUS_CORE",
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter { "system:windows" }
		systemversion "latest"
		links { "opengl32", "gdi32" }

		defines {
			"ME_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "system:not windows"
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
		"%{IncludeDir.nlohmann}"
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

	buildoptions {
		"/MP"
	}

	filter "system:windows"
		systemversion "latest"
		links { "opengl32", "gdi32" }

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
		"%{IncludeDir.nlohmann}"
	}

	links {
		"Engine"
	}

	defines {
		"MORPHEUS_APP",
		"_CRT_SECURE_NO_WARNINGS"
	}

	buildoptions {
		"/MP"
	}

	filter "system:windows"
		systemversion "latest"
		links { "opengl32", "gdi32" }

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
		os.remove("./Makefile")
		os.remove("./Morpheus.sln")
		os.remove("./Makefile")
		os.remove("./Morpheus/Editor/Editor.vcxproj")
		os.remove("./Morpheus/Editor/Editor.vcxproj.*")
		os.remove("./Morpheus/Editor/Makefile")
		os.remove("./Morpheus/Engine/Engine.vcxproj")
		os.remove("./Morpheus/Engine/Engine.vcxproj.*")
		os.remove("./Morpheus/Engine/Makefile")
		os.remove("./Morpheus/Game/Game.vcxproj")
		os.remove("./Morpheus/Game/Game.vcxproj.*")
		os.remove("./Morpheus/Game/Makefile")
		os.remove("./Libraries/freetype2/FreeType2.vcxproj")
		os.remove("./Libraries/freetype2/FreeType2.vcxproj.*")
		os.remove("./Libraries/freetype2/Makefile")
		os.remove("./Libraries/Glad/Glad.vcxproj")
		os.remove("./Libraries/Glad/Glad.vcxproj.*")
		os.remove("./Libraries/Glad/Makefile")
		os.remove("./Libraries/GLFW/GLFW.vcxproj")
		os.remove("./Libraries/GLFW/GLFW.vcxproj.*")
		os.remove("./Libraries/GLFW/Makefile")
		os.remove("./Libraries/imgui/ImGui.vcxproj")
		os.remove("./Libraries/imgui/ImGui.vcxproj.*")
		os.remove("./Libraries/imgui/Makefile")
		os.remove("./Libraries/lua/Lua.vcxproj")
		os.remove("./Libraries/lua/Lua.vcxproj.*")
		os.remove("./Libraries/nativefiledialog/nfd.vcxproj")
		os.remove("./Libraries/nativefiledialog/nfd.vcxproj.*")
		os.remove("./Libraries/nativefiledialog/Makefile")
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
		print("Done.")
	end
}
