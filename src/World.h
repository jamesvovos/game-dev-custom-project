#pragma once
#include "Location.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "../include/raylib.h"
using namespace std;

class World // World -> Graph
{
public:
    typedef map<string, Location *> vmap;
    vmap locations;
    Location *start_location;
    Player *player;
    bool fileLoaded = false;
    void add_location(const string &id, const string &name, const string &desc, const Vector2 &pos, const Texture2D &texture);
    void add_connection(const string &from, const string &to, string direction);
    void load_file(ifstream &file);
    bool setFileLoaded();
    void update();
    void render();
    World(Player *player);
    ~World();
};