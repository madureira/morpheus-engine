project "Lua"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    warnings "Off"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    makesettings { "CC = gcc" }

    files {
        "src/*.h",
        "src/*.c"
    }

    includedirs { "src" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "Speed"
        defines { "NDEBUG" }
