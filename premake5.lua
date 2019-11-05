workspace "Morpheus"
   architecture "x64"
   startproject "Morpheus"
   configurations { "Debug", "Release" }
   platforms { "x64", "x32" }
   
outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}"
   
IncludeDir = {}
IncludeDir["GLFW"] = "Libraries/GLFW/include"
IncludeDir["Glad"] = "Libraries/Glad/include"

LibrariesDir = {}
LibrariesDir["GLFW"] = "Libraries/GLFW/lib/%{cfg.platform}"

group "Dependencies"
	include "Libraries/Glad"

group ""

project "Morpheus"
   location "Generated"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++11"
   objdir("Build/" .. outputdir)
   targetdir("Dist/" .. outputdir)

   files {
      "%{prj.name}/Source/**.h",
      "%{prj.name}/Source/**.cpp"
   }

   includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
   }

   libdirs
   {
      "%{LibrariesDir.GLFW}"
   }

   links 
	{ 
      "glfw3",
      "Glad"
	}
	
	filter { "system:windows" }
      links { "OpenGL32" }
   
   filter { "system:not windows" }
      links { "GL" }

   filter "system:windows"
		systemversion "latest"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
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
