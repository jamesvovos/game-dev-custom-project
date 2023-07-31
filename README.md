# Game Dev Custom Project.
## _Custom game project showcasing the implementation of different software design patterns and data structures built in C++. This includes the state, composite, component, command and factory design patterns, as well as a graph/node data structure to represent the game world with different locations with adjacent location nodes._

![GameImage](https://i.postimg.cc/PqJjCZCJ/game-project2.png)

## Installation Guide
- Chocolatey installation instructions [Chocolatey website](https://docs.chocolatey.org/en-us/choco/setup)
- C++ installation instructions [C++ Install Tutorial](https://www.youtube.com/watch?v=0HD0pqVtsmw&t=2s)
- Alternative C++ installation instructions [Microsoft website](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-170)

## 1. Install Chocolatey with PowerShell.exe

Install `Chocolatey`
```sh
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
```
## 2. Run the Makefile

Run the Makefile in root/build directory or run the make command from the project root directory:
```sh
g++ src/*.cpp -o game.exe -g -Wall -Wno-missing-braces -Iinclude -Llib -lraylib -opengl32 -lgdi32 -lwinmm -lmingw32
```

## 3. Run the game executable
Once the Make command has been run successfully, there should be a pengl32.exe application ready to run in the projects root directy.
![PenglExampleImage](https://i.postimg.cc/MGNhXLk3/pengl.png)

## Features

- Implementation of Raylib graphics library (no game engine used).
- Implementation of different software design patterns in C++. This includes the state, composite, component, command and factory design patterns.
- Graph and node data structures to represent the game world with different locations. Locations contain a list of adjacent location nodes in which players can travel to.
- Player inventory system using vector data structure.
- Basic axis-aligned bounding box collision detection.
- Audio using Raylib.

## License

MIT
