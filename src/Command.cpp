#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Command.h"
#include "CommandProcessor.h"
#include <sstream>
#include "../include/raylib.h"
using namespace std;

// Base Class
Command::~Command()
{
    delete this;
}

void Command::Execute(string input, Player *player)
{
    cout << "Base Class Execute" << endl;
}

// Go Command

GoCommand::GoCommand() {}

void GoCommand::Execute(string input, Player *player)
{
    // Move player
    player->move();
    //  Grabs the last move on top of the stack
    _movementlog.push(input);
}

// Help Command

HelpCommand::HelpCommand() {}

void HelpCommand::Execute(string input, Player *player)
{
    // Text starting x and y coordinates to display on screen
    int starterX = 190;
    int starterY = 140;

    DrawText("The Adventures of Scarfy :: Help", 190, 80, 20, LIGHTGRAY);
    DrawText("-------------------------------------------------------- ", 190, 100, 20, LIGHTGRAY);
    DrawText("The following commands are supported:", 190, 120, 20, LIGHTGRAY);

    if (!isLoaded)
    {
        // All the commands we want in our program added to dynamic array.
        _availablecommands.push_back("[GO] _, (Press [A] or [D] on the keyboard to move left or right.)");
        _availablecommands.push_back("look at _");
        _availablecommands.push_back("look in _");
        _availablecommands.push_back("inventory");
        _availablecommands.push_back("take _ from _");
        _availablecommands.push_back("put _ in _");
        _availablecommands.push_back("quit");
        setIsLoaded();
    }

    // Printing all commands to screen.
    for (auto c : _availablecommands)
    {
        DrawText(c.c_str(), starterX, starterY, 20, LIGHTGRAY);
        starterY += 20;
    }
    DrawText("Press Enter to return to the Main Menu", 190, starterY, 20, LIGHTGRAY);
}

bool HelpCommand::setIsLoaded()
{
    return isLoaded = true;
}

// Inventory Command

InventoryCommand::InventoryCommand() {}

void InventoryCommand::Execute(string input, Player *player)
{
    player->displayInventory();
}

// Look Command

LookCommand::LookCommand() {}

void LookCommand::Execute(string input, Player *player)
{
    player->look_at();
}

// Attack Command

AttackCommand::AttackCommand() {}

void AttackCommand::Execute(string input, Player *player)
{
    player->getCurrentLocation()->_enemies.at(0)->print();
    player->getCurrentLocation()->_enemies.at(0)->actions["fireball"]->Execute(); // change this to input??
    player->getCurrentLocation()->_enemies.at(0)->print();
}

// Take Command

TakeCommand::TakeCommand() {}

void TakeCommand::Execute(string input, Player *player)
{
    // Just run the "take" command.
    if (input.empty() == true)
    {
        cout << "Please specifiy the [item] you would like to [take] from." << endl;
    }

    // Else take from [item] for example: take [sword] from [bag]
    else if (input.empty() == false)
    {
        stringstream ss(input);
        string keyword, bag, item;
        getline(ss, item, ' ');
        getline(ss, keyword, ' ');
        getline(ss, bag);

        if (keyword == "from")
        {
            player->take(bag, item);
        }
        else
        {
            cout << "Not a valid item to take something from." << endl;
        }
    }
}

// Put Command

PutCommand::PutCommand() {}

void PutCommand::Execute(string input, Player *player)
{
    // Just run the "put" command.
    if (input.empty() == true)
    {
        cout << "Put [item] in [bag]." << endl;
    }

    // Else "put" the [item] into the [bag]
    else if (input.empty() == false)
    {
        stringstream ss(input);
        string keyword, bag, item;
        getline(ss, item, ' ');
        getline(ss, keyword, ' ');
        getline(ss, bag);

        if (keyword == "in")
        {
            player->put(bag, item);
        }
        else
        {
            cout << "Not a valid item to put anywhere." << endl;
        }
    }
}