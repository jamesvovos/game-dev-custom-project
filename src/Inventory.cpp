#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Inventory.h"
#include <algorithm>
#include "../include/raylib.h"
using namespace std;

void Inventory::displayInventory()
{
    int inventorySlotCounter = 0; // keep track of the number of slots taken per row -> once it gets to 3 -> create new row
    int inventorySlotsPerRow = 3; // the number of inventory slots allowed per row in the UI
    int itemSlotX = 660;          // the starter x coordinate of the slots (incremented for each new item added to the player inventory)
    int itemSlotY = 240;          // the starter y coordinate of the slots (incremented for each new item added to the player inventory)

    DrawRectangle(650, 200, 250, 300, BLACK);
    DrawText("Inventory", 725, 205, 20, BLUE);
    for (auto i : _items)
    {
        DrawRectangle(itemSlotX, itemSlotY, 64, 64, GRAY);
        DrawText(i->getName().c_str(), itemSlotX + 10, itemSlotY + 3, 14, BLUE);
        DrawTextureRec(i->getTexture(), Rectangle{0, 0, (float)i->getTexture().width, (float)i->getTexture().height}, {(float)itemSlotX + 15, (float)itemSlotY + 20}, RAYWHITE);

        if (inventorySlotCounter < inventorySlotsPerRow)
        {
            itemSlotX += 80;
            inventorySlotCounter++;
        }
        if (inventorySlotCounter >= inventorySlotsPerRow)
        {
            itemSlotX -= 240;
            itemSlotY += 80;
            inventorySlotCounter = 0;
        }
    }
}

void Inventory::addItem(Backpack *item)
{
    Sound sound = LoadSound("../src/assets/audio/leather_inventory.wav");
    PlaySound(sound);
    _items.push_back(item);
}

void Inventory::removeItem(Backpack *item)
{
    _items.erase(remove(_items.begin(), _items.end(), item), _items.end());
}

vector<Backpack *> Inventory::getItems()
{
    return _items;
}

Inventory::~Inventory() {}

Inventory::Inventory() {}