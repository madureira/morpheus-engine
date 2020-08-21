![](.github/morpheus-logo-text.png?raw=true "Morpheus")

# morpheus-engine

[![Project Status: WIP](https://www.repostatus.org/badges/latest/wip.svg)](https://github.com/madureira/morpheus-engine#todo)
[![language](https://img.shields.io/badge/language-c++-blue.svg)](https://github.com/madureira/morpheus-engine)
[![c++](https://img.shields.io/badge/std-c++17-blue.svg)](https://isocpp.org/)
[![msvc2019+](https://img.shields.io/badge/MSVC-2019+-ff69b4.svg)](https://visualstudio.microsoft.com/downloads)
[![platforms](https://img.shields.io/badge/platforms-Windows10%20%7C%20Linux-lightgray.svg)](https://github.com/madureira/morpheus-engine/tree/linux-build#platforms)

Game engine built in C++ and OpenGL.

> Initial development is underway, but there is still no stable and usable version, suitable for the public.


## [Screenshots](https://github.com/madureira/morpheus-engine/tree/master/.github/screenshots) / [Video](https://www.youtube.com/watch?v=8IatRcdtFdQ)

## Features

- Visual editor (multi-viewport);
- Modern OpenGL features;
- 2D batch rendering;
- 2D Dynamic illumination;
- Normal Map for 2D sprites;
- Specular Map for 2D sprites;
- Basic Lua scripting support;
- PS4 controller support;

## 3rd Party Libraries

The engine use the following libraries:

- [EnTT:](https://github.com/skypjack/entt) Entity-component system (ECS);
- [FreeType2:](https://www.freetype.org/) Render fonts;
- [Glad:](https://glad.dav1d.de/) OpenGL loader;
- [GLFW:](https://www.glfw.org/) Window and input;
- [glm:](https://glm.g-truc.net) OpenGL Mathematics (GLM) is a header only C++ mathematics library;
- [IconFontCppHeaders:](https://github.com/juliettef/IconFontCppHeaders) C++11, C89 headers and C# classes for icon fonts Font Awesome;
- [ImGui:](https://github.com/ocornut/imgui) Immediate Mode Graphical User interface;
- [ImGuiColorTextEdit:](https://github.com/BalazsJako/ImGuiColorTextEdit) Syntax highlighting text editor for ImGui;
- [Lua:](https://www.lua.org/) Script language;
- [nativefiledialog:](https://github.com/mlabbe/nativefiledialog) A tiny, neat C library that portably invokes native file open and save dialogs;
- [nlohmann:](https://github.com/nlohmann/json) JSON for Modern C++;
- [Premake:](https://premake.github.io/index.html) Build configuration;
- [sol3:](https://github.com/ThePhD/sol2) A C++ library binding to Lua;
- [spdlog:](https://github.com/gabime/spdlog) Very fast, header-only/compiled, C++ logging library;
- [stb_image:](https://github.com/nothings/stb) Image loading/decoding from file/memory;
- [TiledParser:](https://github.com/madureira/TiledParser) Tiled parser;

## Platforms

![Windows](.github/windows-logo.png "windows")

### Building for Visual Studio IDE 2019

```
install.bat
```

Double click on the generated `Morpheus.sln` file.

### Clean installation files

```
clean.bat
```

---

![Linux](.github/linux-logo.png "Linux")

```
sudo apt-get install -y build-essential xorg-dev libgtk-3-dev mingw-w64
```

### Building Makefiles

```
./install.sh
```

### Building the Engine

```
make
```

The engine executable will be placed at: `Dist/linux/Debug/x64/Editor/` (depending on your machine architecture).

> You need to enter in the above directory to run the executable file.

### Clean installation files

```
./clean.sh
```
