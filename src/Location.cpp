#include "Location.h"
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// Constructor
// Location::Location(string _id, string _name, string _desc) : id(_id), name(_name), desc(_desc) {}

string Location::getName() { return name; }

string Location::getDescription() { return desc; }

void Location::getConnections()
{
    for (auto e : adj)
    {
        cout << "You can move: " + e.first + " " + "to " + "[" + e.second->name + "]" << endl;
    }
}

void Location::print()
{
    printf("Location [%s]: ", name.c_str());
    for (auto e : adj)
        printf(" -> [%s] (direction=%s), ",
               e.second->name.c_str(),
               e.first.c_str());
    printf("\n");
};

void Location::addItem(Backpack *item)
{
    _items.push_back(item);
}

void Location::removeItem(Backpack *item)
{
    _items.erase(remove(_items.begin(), _items.end(), item), _items.end());
}

// void Location::viewItems()
// {
//     cout << "------- Items in this location: -------" << endl;
//     for (auto i : _items)
//         cout << i->getName() << endl;
//     cout << "---------------------------------------" << endl;
// }

void Location::addEnemy(Enemy *enemy)
{
    _enemies.push_back(enemy);
}

void Location::viewEnemies()
{
    for (auto e : _enemies)
    {
        cout << "There is a " << e->name << " here." << endl;
        cout << "Be warned... " << e->desc << endl;
    }
}

void Location::addDoor(Door *door)
{
    _doors.push_back(door);
}

void Location::render()
{
    DrawTextureRec(_texture, Rectangle{0, 0, (float)_texture.width, (float)_texture.height}, _mapBackgroundPosition, RAYWHITE);
    for (auto i : _items)
    {
        i->render();
    }
    for (auto d : _doors)
    {
        d->render();
    }
    for (auto e : _enemies)
    {
        e->render();
    }
}

Location::~Location()
{
    for (auto i : _items)
    {
        i->~Backpack();
    }
    for (auto e : _enemies)
    {
        for (auto a : e->actions)
        {
            delete a.second;
        }
        e->~Enemy();
    }
    for (auto d : _doors)
    {
        d->~Door();
    }
    UnloadTexture(_texture);
    delete this;
}
