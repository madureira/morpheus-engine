<p align="center">
    <img src=".github/morpheus-logo-text.png?raw=true"/>
    <br/>
    <a aria-label="Project Status" href="https://github.com/madureira/morpheus-engine">
        <img src="https://www.repostatus.org/badges/latest/wip.svg"/>
    </a>
    <a aria-label="language" href="https://github.com/madureira/morpheus-engine">
        <img src="https://img.shields.io/badge/language-c++-blue.svg"/>
    </a>
    <a aria-label="c++" href="https://github.com/madureira/morpheus-engine">
        <img src="https://img.shields.io/badge/std-c++17-blue.svg"/>
    </a>
    <a aria-label="msvc2019+" href="https://visualstudio.microsoft.com/downloads">
        <img src="https://img.shields.io/badge/MSVC-2019+-ff69b4.svg"/>
    </a>
    <a aria-label="platforms" href="https://github.com/madureira/morpheus-engine#Platforms">
        <img src="https://img.shields.io/badge/platforms-Windows%20%7C%20Linux%20%7C%20MacOSX-orange.svg"/>
    </a>
</p>

<p align="center">Game Engine built in C++ and OpenGL.</p>

<br/>


> Initial development is underway, but there is still no stable and usable version, suitable for the public.

## Features

- Cross platform (Windows and Linux);
- Visual editor (multi-viewport);
- Modern OpenGL features;
- 2D batch rendering;
- 2D Dynamic illumination;
- Normal Map for 2D sprites;
- Specular Map for 2D sprites;
- Multiple file uploading (Drag and Drop);
- Basic Lua scripting support;
- PS4 controller support;

## Platforms

![Windows](.github/windows-logo.png "windows")

### Building for [Visual Studio IDE 2019](https://visualstudio.microsoft.com/downloads)

```
install.bat
```

Double click on the generated `Morpheus.sln` file.

### Clean installation files

```
clean.bat
```

![Linux](.github/linux-logo.png "Linux")

### Install build dependencies

```
sudo apt-get install -y build-essential xorg-dev libgtk-3-dev mingw-w64
```

### Building Makefiles

```
./install.sh
```

### Building the Engine

```
make config=release_x64
```

### Running the Engine

```
cd Dist/linux/Release/x64/Editor/ && ./Editor
```

### Clean installation files

```
./clean.sh
```

![MacOSX](.github/macosx-logo.png "MacOSX")

### Building Makefiles

```
./install.sh
```

### Building the Engine

```
make config=release_x64
```

### Running the Engine

```
cd Dist/macosx/Release/x64/Editor/ && ./Editor
```

### Clean installation files

```
./clean.sh
```

<br/>

## :camera: [Screenshots](https://github.com/madureira/morpheus-engine/tree/master/.github/screenshots) / :movie_camera: [Video](https://www.youtube.com/watch?v=8IatRcdtFdQ)

<p align="center">
    <img src=".github/screenshots/main_screenshot.png?raw=true"/>
</p>

## 3rd Party Libraries

The Engine uses the following libraries:

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
