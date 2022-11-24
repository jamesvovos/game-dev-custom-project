#include "World.h"
#include "Window.h"
#include "GameManager.h"
#include "Command.h"
#include "CommandProcessor.h"
#include "Item.h"
#include "Inventory.h"
#include "Player.h"
#include "Location.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    Inventory inventory;
    Player p(&inventory);
    auto w = World(&p);
    GameManager manager(&w, &p);

    // creates game window which runs the game loop -> update & render functions
    Window *window = new Window(&manager);

    if (!manager.running())
    {
        window->~Window();
    }

    return 0;
}