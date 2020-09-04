project "nfd"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    warnings "Off"
    defines { "_CRT_SECURE_NO_WARNINGS" }

    files {
        "src/*.h",
        "src/include/*.h",
        "src/nfd_common.c",
    }

    includedirs { "src/include/" }

    filter "system:windows"
        language "C++"
        files { "src/nfd_win.cpp" }

    filter "action:gmake or action:xcode4"
        buildoptions { "-fno-exceptions" }

    filter "system:macosx"
        language "C"
        files { "src/nfd_cocoa.m" }

    filter { "system:linux" }
        language "C"
        files { "src/nfd_gtk.c" }
        buildoptions { "`pkg-config --cflags gtk+-3.0`" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Debug"
        defines { "DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "Speed"
        defines { "NDEBUG" }
