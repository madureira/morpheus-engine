project "FreeType2"
    kind "StaticLib"
    language "C"
	staticruntime "On"
	warnings "Off"
	defines {
		"FT2_BUILD_LIBRARY",
		"_CRT_SECURE_NO_WARNINGS"
	}

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
    {
		"include"
	}

    files
    {
		"src/autofit/autofit.c",
		"src/base/ftbase.c",
		"src/base/ftbbox.c",
		"src/base/ftbitmap.c",
		"src/base/ftdebug.c",
		"src/base/ftfstype.c",
		"src/base/ftglyph.c",
		"src/base/ftgxval.c",
		"src/base/ftinit.c",
		"src/base/ftlcdfil.c",
		"src/base/ftmm.c",
		"src/base/ftotval.c",
		"src/base/ftpatent.c",
		"src/base/ftpfr.c",
		"src/base/ftstroke.c",
		"src/base/ftsynth.c",
		"src/base/ftsystem.c",
		"src/bdf/bdf.c",
		"src/cache/ftcache.c",
		"src/cff/cff.c",
		"src/cid/type1cid.c",
		"src/gzip/ftgzip.c",
		"src/lzw/ftlzw.c",
		"src/pcf/pcf.c",
		"src/pfr/pfr.c",
		"src/psaux/psaux.c",
		"src/pshinter/pshinter.c",
		"src/psnames/psmodule.c",
		"src/raster/raster.c",
		"src/sfnt/sfnt.c",
		"src/smooth/smooth.c",
		"src/truetype/truetype.c",
		"src/type1/type1.c",
		"src/type42/type42.c",
		"src/winfonts/winfnt.c"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
