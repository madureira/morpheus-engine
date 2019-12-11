# morpheus-engine

[![Project Status: WIP](https://www.repostatus.org/badges/latest/wip.svg)](https://github.com/madureira/morpheus-engine#todo)
[![language](https://img.shields.io/badge/language-c++-blue.svg)](https://github.com/madureira/morpheus-engine)
[![c++](https://img.shields.io/badge/std-c++17-blue.svg)](https://isocpp.org/)
[![msvc2019+](https://img.shields.io/badge/MSVC-2019+-ff69b4.svg)](https://visualstudio.microsoft.com/downloads)
[![platform](https://img.shields.io/badge/platform-Windows10-blue.svg)](https://www.microsoft.com/en-us/windows/)
[![platform](https://img.shields.io/badge/platform-Ubuntu-orange.svg)](https://www.ubuntu.com)

A simple game engine built in C++ and OpenGL.

> Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.

![](.github/morpheus-logo.png?raw=true "Morpheus")

## [Screenshots](https://github.com/madureira/morpheus-engine/tree/master/.github/screenshots) / [Video](https://www.youtube.com/watch?v=8IatRcdtFdQ)

## Features

- Support for Windows and Linux;
- Modern OpenGL features;
- 2D batch rendering;
- Normal Map for 2D sprites;
- 2D Dynamic illumination;
- Basic Lua scripting support;
- PS4 controller support;

## Third Party

The engine use the following libraries:

- [EnTT:](https://github.com/skypjack/entt) Entity-component system (ECS);
- [FreeType2:](https://www.freetype.org/) Render fonts;
- [Glad:](https://glad.dav1d.de/) OpenGL loader;
- [GLFW:](https://www.glfw.org/) Window and input;
- [glm:](https://glm.g-truc.net) OpenGL Mathematics (GLM) is a header only C++ mathematics library;
- [IconFontCppHeaders:](https://github.com/juliettef/IconFontCppHeaders) C++11, C89 headers and C# classes for icon fonts Font Awesome;
- [ImGui:](https://github.com/ocornut/imgui) Immediate Mode Graphical User interface;
- [Lua:](https://www.lua.org/) Script language;
- [Premake:](https://premake.github.io/index.html) Build configuration;
- [sol3:](https://github.com/ThePhD/sol2) A C++ library binding to Lua;
- [spdlog:](https://github.com/gabime/spdlog) Very fast, header-only/compiled, C++ logging library;
- [stb_image:](https://github.com/nothings/stb) Image loading/decoding from file/memory;

## Platforms

![Windows](.github/windows-logo.png?raw=true "windows10")

## Windows

### Building for Visual Studio IDE 2019

```
install.bat
```

Double click on the generated `Morpheus.sln` file.

### Clean installation files

```
clean.bat
```

![Linux](.github/linux-logo.png?raw=true "Linux")

## Linux (WIP)

Generating Makefile

```
./install.sh
```

### Building

```
make
```

### Clean installation files

```
./clean.sh
```

---

## TODO

- [ ] Allow creating a new project through the editor;
- [ ] Allow building the project through the editor;
- [ ] Generate the game executable through the editor;
