#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Player.h"
#include <algorithm>
using namespace std;

void Player::displayInventory()
{
    _inventory->displayInventory();
}

void Player::addItemToInventory(Backpack *item)
{
    _inventory->addItem(item);
}

void Player::removeItemFromInventory(Backpack *item)
{
    _inventory->removeItem(item);
}

Location *Player::getCurrentLocation()
{
    return current_location;
}

Location *Player::setCurrentLocation(Location *updatedLocation)
{
    return current_location = updatedLocation;
}

void Player::animate()
{
    timer += GetFrameTime();

    if (timer >= 0.2)
    {
        timer = 0.0f;
        frame += 1;
    }

    frame = frame % maxFrames;
}

void Player::move()
{
    if (IsKeyDown(KEY_D))
    {
        animate();
        position.x += GetFrameTime() * speed;
    }
    if (IsKeyDown(KEY_A))
    {
        animate();
        position.x -= GetFrameTime() * speed;
    }
};

void Player::look_at()
{
    // Item Collisions
    for (auto i : getCurrentLocation()->_items)
    {
        if (!getCurrentLocation()->_items.empty()) // check that the location has "items" to collide with first.
        {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionCircles(mousePos, 5, i->getPosition(), 20))
            {
                string itm = i->getName().c_str();
                DrawText(i->getDesc().c_str(), 190, 90, 20, BLACK);
                look_in(itm);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    addItemToInventory(i);
                    getCurrentLocation()->removeItem(i);
                }
            }
        }
    }
}

void Player::look_in(string &item)
{
    for (auto i : getCurrentLocation()->_items)
    {
        if (i->getName() == item)
        {
            i->displayDetails();
        }
    }
}

void Player::take(string &bag, string &item)
{
    for (auto i : getCurrentLocation()->_items)
    {
        if (i->getName() == bag)
        {
            vector<Backpack *> _itemsInBag = i->getItems();
            for (auto itm : _itemsInBag)
            {
                if (itm->getName() == item)
                {
                    // Removes the item from the bag.
                    i->remove(itm);
                    // Adds the item to the players inventory (as it has been taken out of the bag!)
                    addItemToInventory(itm);
                    cout << "[" << itm->getName() << "]"
                         << " added to player inventory" << endl;
                }
            }
        }
    }
}

void Player::put(string &bag, string &item) // NOTE: this will currently crash if the item is removed from the location already.
{
    Backpack *itm;
    for (auto i : getCurrentLocation()->_items)
    {

        if (i->getName() == item)
        {
            itm = i; // assign it to local variable for use later with the "bag".
        }

        // Adds the item to the bag
        if (i->getName() == bag)
        {
            // Adds the item to the bag
            i->add(itm);
            Sound sound = LoadSound("../src/assets/audio/cloth-inventory.wav");
            PlaySound(sound);
            // Prints out the item name added to the bag
            cout << "[" << itm->getName() << "]"
                 << " added to Bag" << endl;
            // Removes the item from the Location (as it is now in the bag)
            getCurrentLocation()->removeItem(itm);
        }
    }
    // allows the put function to add items to bag, even if the bag is not in the world location (i.e in the players inventory)
    for (auto a : _inventory->getItems())
    {
        // Adds the item to the bag
        if (a->getName() == bag)
        {
            // Adds the item to the bag
            a->add(itm);
            // Prints out the item name added to the bag
            cout << "[" << itm->getName() << "]"
                 << " added to Bag" << endl;
            // Removes the item from the Location (as it is now in the bag)
            getCurrentLocation()->removeItem(itm);
        }
    }
}

void Player::location_details()
{
    DrawText("You are in: ", 190, 30, 20, WHITE);
    DrawText(getCurrentLocation()->getName().c_str(), 190, 50, 20, WHITE);
    DrawText(getCurrentLocation()->getDescription().c_str(), 190, 70, 20, WHITE);
};

Player::Player(Inventory *inventory)
{
    _inventory = inventory;
}

Texture2D Player::setTexture(Texture2D &_texture)
{
    return texture = _texture;
}

void Player::render()
{
    location_details(); // move this later
    DrawTextureRec(texture, Rectangle{(frameWidth * frame), 0, frameWidth, (float)texture.height}, position, RAYWHITE);
}

void Player::checkIfGoingThroughDoor()
{
    // Door Collisions
    if (!getCurrentLocation()->_doors.empty()) // check that the location has a door to collide with first.
    {
        if (CheckCollisionCircles(position, 5, getCurrentLocation()->_doors.at(0)->getPosition(), 40))
        {
            current_location = current_location->adj.at(0).second;
        }
    }
}

Vector2 Player::getPosition()
{
    return position;
}