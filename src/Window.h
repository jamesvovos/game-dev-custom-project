#pragma once
#include <iostream>
#include <vector>
#include "../include/raylib.h"
using namespace std;

// forward declaration
class GameManager;

// Game Window Raylib -> pass to states to use
class Window
{
protected:
    GameManager *_manager = nullptr; // NEW
    int windowWidth = 900;
    int windowHeight = 450;

public:
    Window(GameManager *manager);
    ~Window();
};