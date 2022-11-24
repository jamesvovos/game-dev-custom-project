#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include <algorithm>
#include "Item.h"
using namespace std;

// https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position

// Abstract component base class "Backpack" -> can contain a "bag" or just "items" or a "bag with items"

void Backpack::add(Backpack *b) {}

void Backpack::remove(Backpack *item) {}

vector<Backpack *> Backpack::getItems()
{
    return _backpackitems;
}

Backpack::~Backpack()
{
    delete this;
}

// Bag Composite

string Bag::getName()
{
    return _name;
}

string Bag::getDesc()
{
    return _desc;
}

void Bag::add(Backpack *b)
{
    _bagitems.push_back(b);
}

void Bag::remove(Backpack *item)
{
    _bagitems.erase(std::remove(_bagitems.begin(), _bagitems.end(), item), _bagitems.end());
}

void Bag::displayDetails()
{
    int titleX = 10;     // the starter x coordinate of the bag open title
    int titleY = 130;    // the starter y coordinate of the bag open title
    int itemSlotX = 10;  // the starter x coordinate of the slots (incremented for each new item added to the player inventory)
    int itemSlotY = 150; // the starter y coordinate of the slots (incremented for each new item added to the player inventory)

    // UI that lists the items in the bag.
    DrawText("You've untied the string and find:", titleX, titleY, 20, BLACK);
    for (auto i : _bagitems)
    {
        DrawRectangle(itemSlotX, itemSlotY, 150, 32, BLUE);
        DrawTextureRec(i->getTexture(), Rectangle{0, 0, (float)i->getTexture().width, (float)i->getTexture().height}, {(float)itemSlotX, (float)itemSlotY}, RAYWHITE);
        DrawText(i->getName().c_str(), itemSlotX + 40, itemSlotY, 20, BLACK);
        itemSlotY += 40;
    }
}

void Bag::render()
{
    DrawTextureRec(_texture, Rectangle{200, 0, (float)_texture.width, (float)_texture.height}, _position, RAYWHITE);
}

Texture2D Bag::getTexture()
{
    return _texture;
}

Vector2 Bag::getPosition()
{
    return _position;
}

vector<Backpack *> Bag::getItems()
{
    return _bagitems;
}

Bag::~Bag()
{
    for (auto i : _bagitems)
    {
        delete i;
    }
    UnloadTexture(_texture);
    delete this;
}

// Item Leaf -> Only Operations()

string Item::getName()
{
    return _name;
}

string Item::getDesc()
{
    return _desc;
}

void Item::displayDetails()
{
    DrawText("You cannot look into this item.", 190, 110, 20, RED);
}

Item::~Item()
{
    UnloadTexture(_texture);
    delete this;
}

void Item::render()
{
    DrawTextureRec(_texture, Rectangle{0, 0, (float)_texture.width, (float)_texture.height}, _position, RAYWHITE);
}

Texture2D Item::getTexture()
{
    return _texture;
}

Vector2 Item::getPosition()
{
    return _position;
}
