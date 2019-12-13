newoption {
   trigger     = "linux_backend",
   value       = "B",
   description = "Choose a dialog backend for linux",
   allowed = {
      { "gtk3", "GTK 3 - link to gtk3 directly" },
      { "zenity", "Zenity - generate dialogs on the end users machine with zenity" }
   }
}

if not _OPTIONS["linux_backend"] then
   _OPTIONS["linux_backend"] = "gtk3"
end

project "nfd"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs {
		"src/include/"
	}

	-- common files
	files {
		"src/*.h",
		"src/include/*.h",
		"src/nfd_common.c",
	}

	warnings "extra"

	-- system build filters
	filter "system:windows"
		language "C++"
		files {"src/nfd_win.cpp"}

	filter {"action:gmake or action:xcode4"}
		buildoptions {"-fno-exceptions"}

	filter "system:macosx"
		language "C"
		files {"src/nfd_cocoa.m"}

	filter {"system:linux", "options:linux_backend=gtk3"}
		language "C"
		files {"src/nfd_gtk.c"}
		buildoptions {"`pkg-config --cflags gtk+-3.0`"}

	filter {"system:linux", "options:linux_backend=zenity"}
		language "C"
		files {"src/nfd_zenity.c"}
