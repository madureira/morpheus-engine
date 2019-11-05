workspace "morpheus"
   architecture "x64"
   startproject "morpheus"
   configurations { "Debug", "Release" }
   platforms { "x64", "x32" }

outputdir = "%{cfg.system}/%{cfg.buildcfg}/%{cfg.platform}"

project "morpheus"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   objdir("build/" .. outputdir)
   targetdir("bin/" .. outputdir)

   files {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }

   filter "system:windows"
		systemversion "latest"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
