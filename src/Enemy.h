#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include <map>
#include "Attribute.h"
#include "Action.h"
#include "../include/raylib.h"
#include "../include/raymath.h"
using namespace std;

class Enemy
{
public:
    string name;
    string desc;
    bool sound_played = false;
    map<string, int> attributes;
    map<string, Action *> actions;

    bool standing_infront_of_player = false;
    Vector2 position;
    Texture2D texture;
    Vector2 target;
    void render();
    Vector2 calculate();
    void update();
    void print();
    Enemy(string _name, string _desc, Vector2 _position, Texture2D _texture, Vector2 _target);
    ~Enemy();
};