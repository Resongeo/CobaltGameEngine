# Cobalt Game Engine

Simple 2D engine written in C++. The core engine and parts of the editor based on The Cherno's [Game Engine series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT).
The main goal of this project for me is to learn C++, game engine architecture and game programming.
> The engine is in a very early stage, not capable of creating games yet.

## Dependencies
The project includes all the dependency. Dependencies are below
- [entt](https://github.com/skypjack/entt)
- [GLAD](https://glad.dav1d.de/)
- [GLFW](https://www.glfw.org/)
- [GLM](https://github.com/g-truc/glm)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
- [stb](https://github.com/nothings/stb)
 
## Platforms
- Windows

## Requirements
- Visual Studio 2022
- Windows 10 SDK
- Python 3.x

## Building and running
- Clone this repository
``` bash
git clone --recursive https://github.com/Resongeo/CobaltGameEngine -b dev
```
- Change the directory
``` bash
cd CobaltGameEngine
```
- Run `GenerateProject.py` python script
``` bash
python .\Tools\GenerateProject.py
```
> If running the first time it will prompt you to download the premake binaries
- Open `CobaltGameEngine.sln` file and run the project with `f5`