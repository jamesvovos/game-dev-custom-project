#pragma once
#include <iostream>
#include "../include/raylib.h"
using namespace std;

class Door
{
protected:
    Vector2 _position;
    Texture2D _texture;

public:
    Door(Vector2 position, Texture2D texture);
    ~Door();
    void render();
    Vector2 getPosition();
};