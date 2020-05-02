project "TiledParser"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	makesettings { "CC = gcc" }

	includedirs {
        "../nlohmann/include",
		"./include"
	}

	files {
        "./include/TiledParser/Base64.h",
        "./include/TiledParser/Layer.h",
        "./include/TiledParser/Layer.cpp",
        "./include/TiledParser/Object.h",
        "./include/TiledParser/Object.cpp",
        "./include/TiledParser/ObjectGroup.h",
        "./include/TiledParser/ObjectGroup.cpp",
        "./include/TiledParser/TileLayer.h",
        "./include/TiledParser/TileLayer.cpp",
        "./include/TiledParser/TileSet.h",
        "./include/TiledParser/TileSet.cpp",
        "./include/TiledParser/TileMap.h",
        "./include/TiledParser/TileMap.cpp"
	}

	filter "system:windows"
		systemversion "latest"

    filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		optimize "Debug"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "Speed"
