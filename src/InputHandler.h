#pragma once
#include <iostream>
#include <vector>
#include "../include/raylib.h"
using namespace std;

// forward decleration
class GameManager;

#define MAX_INPUT_CHARS 20

class InputHandler
{
private:
    GameManager *_manager = nullptr;          // NEW
    char command[MAX_INPUT_CHARS + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;
    Rectangle textBox = {170, 180, 490, 50};
    bool mouseOnText = false;
    int framesCounter = 0;

public:
    InputHandler(GameManager *manager);
    void render();
    void update();
    bool IsAnyKeyPressed();
    ~InputHandler();
};