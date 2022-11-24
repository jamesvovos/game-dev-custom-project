#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Item.h"
#include "Inventory.h"
#include "Location.h"
#include "../include/raylib.h"
using namespace std;

class Player
{
private:
    Inventory *_inventory = nullptr;
    Location *current_location;
    float speed = 200.0f;
    float x = -25.0f;
    float y = 265.0f;
    Vector2 position = {x, y};
    Texture2D texture;

    // Sprite Animation Stuff -> maybe create a Sprite class later to handle this?
    float textureWidth = 768.0f;
    float spriteFrames = 6.0f;
    float frameWidth = textureWidth / spriteFrames;
    float timer = 0.0f;
    int frame = 0;
    int maxFrames = (int)(768 / (int)frameWidth);

public:
    void displayInventory();
    void addItemToInventory(Backpack *item);
    void removeItemFromInventory(Backpack *item);
    Location *getCurrentLocation();
    Location *setCurrentLocation(Location *updatedLocation);
    void location_details();
    void move();
    void look_at();
    void look_in(string &item);
    void take(string &bag, string &item);
    void put(string &bag, string &item);
    Texture2D setTexture(Texture2D &_texture);
    void render();
    void animate();
    void checkIfGoingThroughDoor();
    Vector2 getPosition();
    Player(Inventory *inventory);
};