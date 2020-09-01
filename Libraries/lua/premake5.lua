project "Lua"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    warnings "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    makesettings { "CC = gcc" }

    includedirs {
        "src"
    }

    files {
        "src/*.h",
        "src/*.c"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
