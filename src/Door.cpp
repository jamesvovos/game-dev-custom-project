#include <iostream>
#include "Door.h"
#include "../include/raylib.h"
using namespace std;

Door::Door(Vector2 position, Texture2D texture) : _position(position), _texture(texture) {}

Door::~Door()
{
    UnloadTexture(_texture);
    delete this;
}

void Door::render()
{
    DrawTextureRec(_texture, Rectangle{0, 0, (float)_texture.width, (float)_texture.height}, _position, RAYWHITE);
}

Vector2 Door::getPosition()
{
    return _position;
}