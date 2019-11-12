workspace "Morpheus"
   architecture "x64"
   startproject "Morpheus"
   configurations { "Debug", "Release" }
   platforms { "x64", "x32" }
   
outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}"
   
IncludeDir = {}
IncludeDir["GLFW"] = "Libraries/GLFW/include"
IncludeDir["Glad"] = "Libraries/Glad/include"
IncludeDir["lua"] = "Libraries/lua/src"
IncludeDir["sol3"] = "Libraries/sol3/include"

LibrariesDir = {}
LibrariesDir["GLFW"] = "Libraries/GLFW/lib/%{cfg.platform}"

group "Dependencies"
   include "Libraries/Glad"
   include "Libraries/lua"

group ""

project "Morpheus"
   location "Morpheus"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   objdir("Build/" .. outputdir)
   targetdir("Dist/" .. outputdir)

   files {
      "%{prj.name}/Source/**.h",
      "%{prj.name}/Source/**.cpp",
      "%{prj.name}/Source/**.lua"
   }

   includedirs
	{
      "%{prj.name}/Source",
		"%{IncludeDir.GLFW}",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.lua}",
      "%{IncludeDir.sol3}"
   }

   libdirs
   {
      "%{LibrariesDir.GLFW}"
   }

   links 
	{ 
      "glfw3",
      "Glad",
      "lua"
	}

	filter { "system:windows" }
      systemversion "latest"
      links { "OpenGL32" }
      postbuildcommands {
         "mkdir %{prj.location}..\\Dist\\windows\\Debug\\x64\\Config",
         "mkdir %{prj.location}..\\Build\\windows\\Debug\\x64\\Config",
         "copy %{prj.location}Source\\Config\\engine.lua %{prj.location}..\\Dist\\windows\\Debug\\x64\\Config\\engine.lua",
         "copy %{prj.location}Source\\Config\\engine.lua %{prj.location}..\\Build\\windows\\Debug\\x64\\Config\\engine.lua",
      }
   
   filter { "system:not windows" }
      links { "GL" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      kind "WindowedApp"
      flags { entrypoint "mainCRTStartup" }
      optimize "On"


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
