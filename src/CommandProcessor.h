#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <map>
#include "Command.h"
using namespace std;

// https://en.wikipedia.org/wiki/Command_pattern
// https://refactoring.guru/design-patterns/command/cpp/example#:~:text=Command%20in%20C%2B%2B,Learn%20more%20about%20Command

// Invoker
class CommandProcessor
{
private:
    Player *player;
    World *world;

public:
    // all commands our game will handle
    map<string, Command *> commands;

    void runCommand(string input);

    void showCommands();

    // Destructor
    ~CommandProcessor();

    // Constructor
    CommandProcessor(Player *player, World *world);
};