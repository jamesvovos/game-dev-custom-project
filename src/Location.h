#pragma once
#include <iostream>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include "Door.h"
#include "../include/raylib.h"

using namespace std;

struct Location // Location -> Node
{
    typedef pair<string, Location *> nd;
    vector<nd> adj;            // each has a direction, destination
    vector<Backpack *> _items; // items/entities at each location (can be empty -> so don't init in constructor)
    vector<Enemy *> _enemies;  // enemies situated at each location
    vector<Door *> _doors;     // doors situated at each location
    string id;
    string name;
    string desc;
    Vector2 _mapBackgroundPosition; // position of the map background image
    Texture2D _texture;             // location scene image

    // Constructor
    Location(string _id, string _name, string _desc, Vector2 _pos, Texture2D texture) : id(_id), name(_name), desc(_desc), _mapBackgroundPosition(_pos), _texture(texture){};
    string getName();
    string getDescription();
    void getConnections();
    void print();
    void addItem(Backpack *item);
    void removeItem(Backpack *item);
    void addEnemy(Enemy *enemy);
    void viewEnemies();
    void addDoor(Door *door);
    void render();
    ~Location();
};